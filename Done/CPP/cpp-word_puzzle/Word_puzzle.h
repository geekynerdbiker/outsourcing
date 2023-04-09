#pragma once

#include "matrix.h"
#include <vector>
#include <string>


using namespace std;

class Word_puzzle
{
public:
	Word_puzzle(const string& puzzle_file, const int numrows, const int numcols);
	~Word_puzzle();

	void print_puzzle();
	void read_dic_file(const string & dic_file);
private:
	matrix<string> m_puzzle; // 그림 1.1에 있는 것처럼, 2차원 퍼즐이고 글자가 저장되어 있음
};

