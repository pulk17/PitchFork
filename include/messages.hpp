#pragma once
#include <cstdint>

#pragma pack(1)
struct AddOrder{
    char msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t timestamp[6];
    uint64_t order_ref;
    char side;
    uint32_t shares;
    char stock[8];
    uint32_t price;
};

struct DeleteOrder{
    char msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t timestamp[6];
    uint64_t order_ref;
};

struct SystemEvent{
    char msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t timestamp[6];
    char eventcode;
};
#pragma pack()
