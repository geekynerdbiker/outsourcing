#pragma once
#include <iostream>

using namespace std;

class Matrix {
public:
	Matrix();
    static const int SIZE = 3;
	
    const int getElement(int, int) const;
    void setElement(int, int, int);
    
	const int getWidth() const;
    void setWidth();
	
    const int getSize() const;
    
	const Matrix operator +(const Matrix&) const;
	const Matrix operator *(const Matrix&) const;
private:
    int width;
    int matrix[SIZE][SIZE];
	void init();
};
istream& operator >>(istream&, Matrix&);
ostream& operator <<(ostream&, const Matrix&);
