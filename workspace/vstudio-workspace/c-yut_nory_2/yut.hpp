#include <cstdlib>
#include <string>
#include <vector>
#ifndef __YUT_H_INCLUDED__
#define __YUT_H_INCLUDED__
using namespace std;

class YutName {
  public:
    YutName(string name) : name(name) {}
    string name;
    bool operator<(const YutName &other) const {
        //////////////////IMPLEMENT HERE//////////////////////////////////////
        return name < other.name;
        //////////////////////////////////////////////////////////////////////
    }
};

class Yut {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    Yut(float prob) : prob(prob) {}
    friend class Player;
    friend class AnimalPlayer;

  private:
    float prob;
    int throwOneYut();
    string throwFourYuts();
};

#endif
