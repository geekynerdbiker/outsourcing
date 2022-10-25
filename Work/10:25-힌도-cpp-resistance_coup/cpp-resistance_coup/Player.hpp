#ifndef EX4_CPP_A_PLAYER_H
#define EX4_CPP_A_PLAYER_H
#pragma once

#include "vector"
#include "string"

class Player{
public:
    std::vector<std::string> role;
    std::string lastAct;
    Player* lastVic;
    int bank;
    
    Player(): bank(0) {};
    virtual ~Player() {};
    
    void push_role(std::string s);
    
    void income();
    void foreign_aid();
    virtual void coup(Player& p);
    
    
};

#endif
