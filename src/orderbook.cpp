#include <iostream>
#include <algorithm>
#include <numeric>

#include "orderbook.hpp"

OrderBook::OrderBook(){
    order_lookup.max_load_factor(0.25);
}

void OrderBook::add_order(Order o){
    order_lookup[o.order_ref] = {o.price, o.side};

    if(o.side == 'B') bids[o.price].push_back(o);
    else asks[o.price].push_back(o);
}

void OrderBook::delete_order(uint64_t order_ref){
    auto it = order_lookup.find(order_ref);
    if(it == order_lookup.end()) return;
    
    OrderMeta& order = it -> second;

    auto& vec = (order.side == 'B') ? bids[order.price] : asks[order.price];
    
    vec.erase(std::remove_if(vec.begin(), vec.end(),
            [&](const Order& o) { return o.order_ref == order_ref; }),
            vec.end());

    if(vec.empty()){
        if(order.side == 'B') bids.erase(order.price);
        else asks.erase(order.price);
    }
    order_lookup.erase(order_ref);
}

void OrderBook::print_top(int levels){
    std::vector<uint32_t> ask_prices;
    for(auto& [price, _] : asks) ask_prices.push_back(price);
    std::sort(ask_prices.begin(), ask_prices.end());
    
    int cnt = 0;
    for(uint32_t price : ask_prices){
        if(cnt++ >= levels) break;
        int shares = std::accumulate(asks[price].begin(), asks[price].end(), 0, 
            [](int sum, const Order& o){ return sum + o.shares; });
        std::cout << "Price = " << price / 10000.0 << " -> Shares = " << shares << "\n"; 
    }

    std::cout << "--------------------------------\n";
    cnt = 0;

    std::vector<uint32_t> bid_prices;
    for (auto& [price, _] : bids) bid_prices.push_back(price);
    std::sort(bid_prices.begin(), bid_prices.end(), std::greater<uint32_t>());

    for(uint32_t price : bid_prices){
        if (cnt++ >= levels) break;
        int shares = std::accumulate(bids[price].begin(), bids[price].end(), 0,
            [](int sum, const Order& o){ return sum + o.shares; });
        std::cout << "Price = " << price / 10000.0 << " -> Shares = " << shares << "\n";
    }
}