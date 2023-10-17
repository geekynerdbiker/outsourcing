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
	matrix<string> m_puzzle; // �׸� 1.1�� �ִ� ��ó��, 2���� �����̰� ���ڰ� ����Ǿ� ����
};

