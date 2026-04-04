#include <iostream>
#include <algorithm>
#include <numeric>

#include "orderbook.hpp"

OrderBook::OrderBook(){
    order_lookup.max_load_factor(0.25);
}

void OrderBook::add_order(Order& o){
    order_lookup[o.order_ref] = {o.price, o.shares, o.side};

    if(o.side == 'B') bids[o.price] += o.shares;
    else asks[o.price] += o.shares;
}

void OrderBook::delete_order(uint64_t order_ref){
    auto it = order_lookup.find(order_ref);
    if(it == order_lookup.end()) return;
    
    OrderMeta& order = it -> second;

    auto& map = (order.side == 'B') ? bids : asks;
    map[order.price] -= order.shares;
    
    if(map[order.price] == 0) map.erase(order.price);
    order_lookup.erase(order_ref);
}

void OrderBook::print_top(int levels){
    std::vector<uint32_t> ask_prices;
    for(auto& [price, _] : asks) ask_prices.push_back(price);
    std::sort(ask_prices.begin(), ask_prices.end());
    
    int cnt = 0;
    for(uint32_t price : ask_prices){
        if(cnt++ >= levels) break;
        std::cout << "Price = " << price / 10000.0 << " -> Shares = " << asks[price] << "\n"; 
    }

    std::cout << "--------------------------------\n";
    cnt = 0;

    std::vector<uint32_t> bid_prices;
    for (auto& [price, _] : bids) bid_prices.push_back(price);
    std::sort(bid_prices.begin(), bid_prices.end(), std::greater<uint32_t>());

    for(uint32_t price : bid_prices){
        if (cnt++ >= levels) break;
        std::cout << "Price = " << price / 10000.0 << " -> Shares = " << bids[price] << "\n";
    }
}