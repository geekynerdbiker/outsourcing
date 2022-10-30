#include "Contessa.hpp"

void Contessa::block(Player &p1, Player& p2) {
    if (p2.lastAct == "assassinate") {
        p2.lastAct = "";
    } else {
        throw std::invalid_argument("Nothing to block!\n");
    }
}
