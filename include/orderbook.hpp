#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <ankerl/unordered_dense.h>
#include <functional>

struct Order{
    uint64_t order_ref;
    uint32_t price; 
    uint32_t shares;
    char side;
};

struct OrderMeta{
    uint32_t price;
    uint32_t shares;
    char side;
};

struct OrderBook{
   ankerl::unordered_dense::map<uint32_t, uint64_t> bids;
   ankerl::unordered_dense::map<uint32_t, uint64_t> asks;
   ankerl::unordered_dense::map<uint64_t, OrderMeta> order_lookup;

    OrderBook();
    void add_order(Order& o);
    void delete_order(uint64_t order_ref);
    void print_top(int levels);
};