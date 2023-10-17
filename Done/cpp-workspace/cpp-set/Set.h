//
//  Set.h
//  cpp-set
//
//  Created by Jacob An on 2022/10/17.
//

#ifndef Set_h
#define Set_h

#include <iostream>

using namespace std;

class Set {
public:
    Set();
    ~Set();
    
    int size, capacity;
    int *elem;
    
    const void resize();
    const int isDup(int) const;
    const Set operator |(const Set&) const;
    const Set operator &(const Set&) const;
    
};

istream& operator >>(istream&, Set&);
ostream& operator <<(ostream&, const Set&);
#endif /* Set_h */
