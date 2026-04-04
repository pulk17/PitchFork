#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <functional>

struct Order{
    uint64_t order_ref;
    uint32_t price; 
    uint32_t shares;
    char side;
};

struct OrderMeta{
    uint32_t price;
    char side;
};

struct OrderBook{
    std::unordered_map<uint32_t, std::vector<Order>> bids;
    std::unordered_map<uint32_t, std::vector<Order>> asks;
    std::unordered_map<uint64_t, OrderMeta> order_lookup;

    OrderBook();
    void add_order(Order o);
    void delete_order(uint64_t order_ref);
    void print_top(int levels);
};