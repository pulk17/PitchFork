#pragma once
#include <cstdint>

#pragma pack(1)
struct AddOrder{
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    char     side;
    uint32_t shares;
    char     stock[8];
    uint32_t price;
};

struct DeleteOrder{
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
};

struct SystemEvent{
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    char     eventcode;
};

struct AddOrderMPID {
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    char     side;
    uint32_t shares;
    char     stock[8];
    uint32_t price;
    char     attribution[4];
};

struct OrderExecuted {
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    uint32_t executed_shares;
    uint64_t match_number;
};

struct OrderExecutedWithPrice {
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    uint32_t executed_shares;
    uint64_t match_number;
    char     printable;
    uint32_t execution_price;
};

struct OrderCancel {
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    uint32_t cancelled_shares;
};

struct OrderReplace {
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t original_order_ref;
    uint64_t new_order_ref;
    uint32_t shares;
    uint32_t price;
};
#pragma pack()
