#include "Player.hpp"
const int MAX_MONEY = 10;
const int COUP_PRICE = 7;
const int INCOME = 1;
const int FOREIGN_VAL = 2;

void Player::push_role(std::string s) {
    this->role.push_back(s);
}

void Player::income() {
    if (this->bank + INCOME >= MAX_MONEY)
        throw std::invalid_argument("You have 10 coins MUST use coup()\n");
    this->bank++;
}

void Player::coup(Player &p) {
    if (this->bank < COUP_PRICE)
        throw std::invalid_argument("Not enough money to coup\n");
    
    this->bank -= COUP_PRICE;
}

void Player::foreign_aid() {
    if (this->bank + FOREIGN_VAL >= MAX_MONEY) {
        throw std::invalid_argument("You have 9-10 coins MUST use coup() or income()\n");
    }
    
    this->bank += FOREIGN_VAL;
    this->lastAct = "foreign_aid";
}

