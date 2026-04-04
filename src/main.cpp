#include <iostream>
#include <cstdint>
#include <string> 
#include <unordered_map>
#include <chrono>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>

#include "messages.hpp"
#include "orderbook.hpp"

int main(){

    int fd = open("/home/pulk1t/LOB/12302019.NASDAQ_ITCH50", O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    size_t file_size = st.st_size;
    const uint8_t* data = (const uint8_t*) mmap (nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    const uint8_t* ptr = data;
    const uint8_t* end = data + file_size; 

    auto books = std::make_unique<OrderBook[]>(65536);  //transfer from stack to heap [65536 is the max size of uint16_t]

    std::unordered_map<uint64_t, uint16_t> ref_to_locate;
    ref_to_locate.reserve(150000000);

    auto starttime = std::chrono::high_resolution_clock::now();
    int message_count = 0;

    while(ptr+2 <= end){
        
        uint16_t length = __builtin_bswap16(*reinterpret_cast<const uint16_t*>(ptr));
        ptr += 2; // exactly 2 bytes to correctly parse the binary
        const char* buffer = reinterpret_cast<const char*>(ptr);
        ptr += length;

        char msg_type = buffer[0];

        if(msg_type == 'A'){
            const AddOrder* msg = reinterpret_cast<const AddOrder*>(buffer);

            uint32_t price = __builtin_bswap32(msg -> price);
            uint32_t shares = __builtin_bswap32(msg -> shares);
            uint64_t order_ref = __builtin_bswap64(msg -> order_ref);
            uint16_t stock_locate = __builtin_bswap16(msg -> stock_locate); 

            Order o;
            o.order_ref = order_ref;
            o.price = price;
            o.shares = shares;
            o.side = msg -> side;
            books[stock_locate].add_order(o);
            ref_to_locate[order_ref] = stock_locate;
        }
        
        if(msg_type == 'D'){
            const DeleteOrder* msg = reinterpret_cast<const DeleteOrder*>(buffer);
            uint64_t order_ref = __builtin_bswap64(msg -> order_ref);
            
            uint16_t stock_locate = ref_to_locate[order_ref];
            books[stock_locate].delete_order(order_ref);
        }

        message_count++;
    }

    std::cout << "Unique order refs: " << ref_to_locate.size() << "\n";

    auto endtime = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration<double>(endtime - starttime).count();
    std::cout << "Processed " << message_count << " messages in " << seconds << "s\n";
    std::cout << "Throughput: " << (message_count / seconds) / 1e6 << " M msg/sec \n";

    return 0;
}