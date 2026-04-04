#include <iostream>
#include <algorithm>
#include <unistd.h>

#include "orderbook.hpp"

OrderBook::OrderBook(){
    order_lookup.max_load_factor(0.25);
}

void OrderBook::add_order(uint64_t order_ref, uint32_t price, uint32_t shares, char side){
    order_lookup[order_ref] = {price, shares, side};

    if(side == 'B') bids[price] += shares;
    else asks[price] += shares;
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

void OrderBook::print_top(int levels, int sock){
    std::vector<uint32_t> ask_prices;
    for(auto& [price, _] : asks) ask_prices.push_back(price);
    std::sort(ask_prices.begin(), ask_prices.end());

    std::vector<uint32_t> bid_prices;
    for(auto& [price, _] : bids) bid_prices.push_back(price);
    std::sort(bid_prices.begin(), bid_prices.end(), std::greater<uint32_t>());

    std::string json = "{\"asks\":[";
    int cnt = 0;
    for(uint32_t price : ask_prices){
        if(cnt++ >= levels) break;
        if(cnt > 1) json += ",";
        json += "[" + std::to_string(price / 10000.0) + "," + std::to_string(asks[price]) + "]";
    }
    json += "],\"bids\":[";
    cnt = 0;
    for(uint32_t price : bid_prices){
        if(cnt++ >= levels) break;
        if(cnt > 1) json += ",";
        json += "[" + std::to_string(price / 10000.0) + "," + std::to_string(bids[price]) + "]";
    }
    json += "]}\n";

    ssize_t _ = write(sock, json.c_str(), json.size());
}

void OrderBook::reduce_order(uint64_t order_ref, uint32_t cancelled_shares){
    auto it = order_lookup.find(order_ref);
    if(it == order_lookup.end()) return;
    
    OrderMeta& order = it -> second;

    auto& map = (order.side == 'B') ? bids : asks;
    map[order.price] -= cancelled_shares;

    if(map[order.price] == 0) map.erase(order.price);

    order.shares -= cancelled_shares;
    if(order.shares == 0) order_lookup.erase(order_ref);
}

void OrderBook::replace_order(uint64_t old_ref, uint64_t new_ref, uint32_t price, uint32_t shares){
    char side = order_lookup[old_ref].side;
    delete_order(old_ref);
    add_order(new_ref, price, shares, side);
}