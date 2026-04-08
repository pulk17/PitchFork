#pragma once
#include <cstdint>

#pragma pack(1)
struct AddOrder{                // 'A'
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

struct DeleteOrder{             // 'X'
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
};

struct SystemEvent{             // 'S'
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    char     eventcode;
};

struct AddOrderMPID {           // 'F'
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

struct OrderExecuted {          // 'E'
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    uint32_t executed_shares;
    uint64_t match_number;
};

struct OrderExecutedWithPrice { // 'C'
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

struct OrderCancel {            // 'X'
    char     msg_type;
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t order_ref;
    uint32_t cancelled_shares;
};

struct OrderReplace {
    char     msg_type;          // 'U'
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    uint64_t original_order_ref;
    uint64_t new_order_ref;
    uint32_t shares;
    uint32_t price;
};

struct StockDirectory {
    char     msg_type;         // 'R'
    uint16_t stock_locate;
    uint16_t tracking;
    uint8_t  timestamp[6];
    char     stock[8];         // left-justified, space-padded — NOT null-terminated
    char     market_category;
    char     financial_status;
    uint32_t round_lot_size;
    char     round_lots_only;
    char     issue_classification;
    char     issue_subtype[2];
    char     authenticity;
    char     short_sale_threshold;
    char     ipo_flag;
    char     luld_ref_price_tier;
    char     etp_flag;
    uint32_t etp_leverage_factor;
    char     inverse_indicator;
};
#pragma pack()
