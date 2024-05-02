//
//  Set.cpp
//  cpp-set
//
//  Created by Jacob An on 2022/10/17.
//

#include "Set.h"

Set::Set() {
    size = 0;
    capacity = 10;
    elem = (int *)malloc(sizeof(int) * 10);
}

Set::~Set() {
//    delete [] elem;
}

const void Set::resize() {
    int* resized = (int *)malloc(sizeof(int) * capacity * 2);
    
    for (int i = 0; i < capacity; i++)
        resized[i] = elem[i];
    free(elem);
    elem = resized;
    resized = NULL;
}

const int Set::isDup(int k) const {
    for (int i = 0; i < size; i++)
        if (elem[i] == k)
            return 1;
    return 0;
}

const Set Set::operator |(const Set& set) const {
    Set tmp;
    
    for (int i = 0; i < size; i++) {
        if (tmp.size == tmp.capacity)
            tmp.resize();
        tmp.elem[tmp.size++] = elem[i];
    }
    for (int i = size; i < size + set.size; i++) {
        if (tmp.size == tmp.capacity)
            tmp.resize();
        if (!tmp.isDup(set.elem[i-size]))
            tmp.elem[tmp.size++] = set.elem[i-size];
    }
    
    return tmp;
}

const Set Set::operator &(const Set& set) const {
    Set tmp;
    
    for (int i = 0; i < size; i++) {
        if (tmp.size == tmp.capacity)
            tmp.resize();
        for (int j = 0; j < set.size; j++) {
            if (elem[i] == set.elem[j])
                tmp.elem[tmp.size++] = elem[i];
        }
    }
    
    return tmp;
}

istream& operator >>(istream& iStream, Set& set) {
    int tmp = 0;
    
    while (true) {
        iStream >> tmp;
        if (tmp < 0) break;
        if (set.isDup(tmp)) {
            cout << tmp << " is deleted as a duplicated element." << endl;
            continue;
        }
        if (set.size == set.capacity) set.resize();
        set.elem[set.size++] = tmp;
    }
    return iStream;
}

ostream& operator <<(ostream& oStream, const Set& set) {
    for (int i = 0; i < set.size; i++) {
        oStream << set.elem[i] << " ";
    }
    return oStream;
}
