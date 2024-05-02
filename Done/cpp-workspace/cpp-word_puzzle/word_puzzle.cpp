#include "Word_puzzle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> make_tokens(const string & str)
{
	char separator = '\t';
	istringstream iss(str);
	string str_buf;
	vector<string> tokens;

	while (getline(iss, str_buf, separator)) 
	{
		tokens.push_back(str_buf);
	}

	return tokens;
}


Word_puzzle::Word_puzzle(const string& puzzle_file, const int numrows, const int numcols)
	: m_puzzle(numrows, numcols)
{
	ifstream ifs;
	ifs.open(puzzle_file, ios::in);
	int row_num = 0;

	string line;
	while (getline(ifs, line)) 
	{
		//cout << line << endl;
		vector<string> tokens = make_tokens(line);
		m_puzzle[row_num++] = tokens;
	}

	ifs.close();
}


Word_puzzle::~Word_puzzle()
{
}

void Word_puzzle::print_puzzle()
{
	for (int i = 0; i < m_puzzle.numrows(); i++)
	{
		vector<string> & row_line = m_puzzle[i];

		for (auto& str : row_line)
		{
			cout << str << "\t";
		}
		cout << endl;
	}

}



