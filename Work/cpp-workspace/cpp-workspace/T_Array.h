#ifndef T_ARRAY_H
#define T_ARRAY_H

#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

enum SortingOrder { INCREASING, DECREASING };
template<typename T, typename K>
class T_Array
{
public:
    T_Array(int n, string nm);
    ~T_Array();
    int size() { return num_elements; }
    bool empty() { return num_elements == 0; }
    string getName() { return name; }
    void insert(int i, T& element);
    void insertion_sort(SortingOrder sortOrder);
    void print(int elements_per_line);
    bool isValidIndex(int i);
    T& operator[](int index) { return t_array[index]; }
private:
    T *t_array;
    int num_elements;
    int capacity;
    string name;
};

template<typename T, typename K>
inline T_Array<T, K>::T_Array(int n, string nm) {
    t_array = NULL;
    num_elements = n;
    capacity = 0;
    name = name;
}

template<typename T, typename K>
inline T_Array<T, K>::~T_Array() {
    
}

template<typename T, typename K>
inline void T_Array<T, K>::insert(int i, T& element) {
    if (num_elements >= capacity) {
        int new_capa;
        new_capa = 2 * capacity;
    }

    if (isValidIndex(i)) {
        for (int j = this->num_elements - 1; j >= i; j--)
            t_array[j + 1] = t_array[j];
        t_array[i] = element;
        num_elements++;
    }
}

template<typename T, typename K>
inline void T_Array<T, K>::insertion_sort(SortingOrder sortOrder) {
    for (int i = 1; i < size(); i++) {
        T curr = t_array[i];
        
        int j = i - 1;
        while (j >= 0 && t_array[j] > curr) {
            t_array[j + 1] = t_array[j];
          j--;
        }
        t_array[j + 1] = curr;
      }
}

template<typename T, typename K>
inline void T_Array<T, K>::print(int elements_per_line) {
    int count = 0;
    
    while (count < num_elements) {
        for (int i = 0; i < elements_per_line; i++) {
            cout << t_array[count] << " ";
            count++;

            if (count % elements_per_line == 0)
                cout << endl;
        }
    }
    cout << endl;
}

template<typename T, typename K>
inline bool T_Array<T, K>::isValidIndex(int index) {
    if (index >= 0 && index < capacity)
        return true;
    else
        return false;
}

#endif // !T_ARRAY_H
