#include "Assassin.hpp"

const int COUP_PRICE = 7;
const int LOWCOST_COUP = 3;

void Assassin::coup(Player &p1, Player& p2) {
    if(p1.bank < LOWCOST_COUP){
        throw std::invalid_argument("Not enough money to coup\n");
    }
    if (p1.bank >= COUP_PRICE){
        p1.bank-=COUP_PRICE;
    }
    else {
        p1.bank -= LOWCOST_COUP;
        p1.lastAct = "assassinate";
        p1.lastVic = &p2;
    }
}
