#include "Duke.hpp"
const int TAX_VAL = 3;
const int BLOCK_VAL = 2;
const int MAX_MONEY = 10;

void Duke::block(Player &p) {
    if(p.lastAct == "foreign_aid"){
        p.bank -= BLOCK_VAL;
    } else {
        throw std::invalid_argument("Nothing to block!\n");
    }
}

void Duke::tax(Player& p) {
    if (p.bank + TAX_VAL >= MAX_MONEY) {
        throw std::invalid_argument("You have too many coins\n");
    }
    
    p.bank += TAX_VAL;
}
