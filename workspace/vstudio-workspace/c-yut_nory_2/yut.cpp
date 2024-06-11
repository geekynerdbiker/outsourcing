#include "yut.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

////////////////// This function is not modifiable!//////////////////////
int Yut::throwOneYut() {
    int res = rand() % 100;
    if (res < prob * 100) {
        return 1; // front
    } else {
        return 0; // back
    }
}
/////////////////////////////////////////////////////////////////////////
/*
- Using the throwOneYut function to get a yut result
- Yut result should be obtained based on the results from the front and back
result of each yut stick.
- One of the yut sticks is marked, so we need to consider the back-do.

- Output
    - yut result (back-do, do, gae, geol, yut, and mo)
*/
string Yut::throwFourYuts() {

    //////////////////IMPLEMENT HERE//////////////////////////////////////
    int marked = rand() % 4;
    bool isMarked = false;

    int res = 0;
    for (int i = 0; i < 4; i++) {
        int yut = throwOneYut();
        if (i == marked && yut == 0)
            isMarked = true;
        res += yut;
    }

    if (res == 3 && !isMarked) return "do";
    else if (res == 3 && isMarked) return "back-do";
    else if (res == 2) return "gae";
    else if (res == 1) return "geol";
    else if (res == 0) return "yut";
    else return "mo";


    //////////////////////////////////////////////////////////////////////
}
