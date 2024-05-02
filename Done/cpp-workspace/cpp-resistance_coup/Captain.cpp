#include "Captain.hpp"

#include <utility>
const int STEAL_VAL = 2;

void Captain::block(Player &p1, Player &p2) {
    if (p2.lastAct == "foreign_aid") {
        p2.bank -= STEAL_VAL;
        p2.lastAct = "";
    } else if (p2.lastAct == "steal") {
        p2.bank -= STEAL_VAL;
        p2.lastVic->bank += STEAL_VAL;
        p2.lastAct = "";
    } else {
        throw std::invalid_argument("Nothing to block!\n");
    }
}

void Captain::steal(Player &p1, Player &p2) {
    if (p2.bank < STEAL_VAL) {
        p1.bank += p2.bank;
        p2.bank = 0;
        p1.lastVic = &p2;
        p1.lastAct = "steal";
    } else{
        p2.bank -= STEAL_VAL;
        p1.bank += STEAL_VAL;
        p1.lastVic = &p2;
        p1.lastAct = "steal";
    }
}
