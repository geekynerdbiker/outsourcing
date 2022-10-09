#include <iostream>
#include "Matrix.h"
#include <string>
#include <iomanip>

using namespace std;

Matrix::Matrix() {
	init();
};

void Matrix::init() {
    for (int y = 0; y < SIZE; y++) {
        width = 0;
        for (int x = 0; x < SIZE; x++) {
            setElement(y, x, 0);
        }
    }
}

const int Matrix::getElement(int y, int x) const { return matrix[y][x]; }
void Matrix::setElement(int y, int x, int value) {
    matrix[y][x] = value;
    string tmp = to_string(value);
    int length = (int)tmp.length();
    
    if (width < length) {
        width = length;
    }
}

const int Matrix::getSize() const { return SIZE; }

const int Matrix::getWidth() const { return width; }
void Matrix::setWidth() {
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			string tmp = to_string(getElement(y, x));
			int length = (int)tmp.length();
			if (width < length) {
				width = length;
			}
		}
	}
}

const Matrix Matrix::operator +(const Matrix& mat2) const {
	Matrix result;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			result.setElement(y, x, matrix[y][x] + mat2.getElement(y, x));
		}
	}
	return result;
}
const Matrix Matrix::operator *(const Matrix& mat2) const {
	Matrix multiplyMat;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int sum = 0;
			for (int k = 0; k < SIZE; k++) {
				sum += matrix[i][k] * mat2.getElement(k, j);
			}
			multiplyMat.setElement(i, j, sum);
		}
	}
	return multiplyMat;
}

istream& operator >>(istream& iStream, Matrix& matrix) {
	int tmp = 0;
    
	for (int y = 0; y < matrix.SIZE; y++) {
		for (int x = 0; x < matrix.SIZE; x++) {
			iStream >> tmp;
			matrix.setElement(y, x, tmp);
		}
	}
	return iStream;
}
ostream& operator <<(ostream& oStream, const Matrix& matrix) {
	for (int y = 0; y < matrix.SIZE; y++) {
		oStream << "|";
		for (int x = 0; x < matrix.SIZE; x++) {
			oStream << setw(matrix.getWidth() + 1) << matrix.getElement(y, x);
		}
		oStream << " |" << endl;
	}
	return oStream;
}
