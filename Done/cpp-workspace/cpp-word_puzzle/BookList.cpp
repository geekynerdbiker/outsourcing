#include "BookList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

BookList::BookList(const string& filename)
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	
	if (ifs.is_open()) {
		string line;
		while (getline(ifs, line)) {
			add_book(line);
		}
		ifs.close();
	}

}

void BookList::print_booklist()
{
	for (auto& book : this->m_books)
	{
		cout << book << endl;
	}
}


void BookList::add_book(const string& book)
{
	m_books.push_back(book);
}

const vector<string>& BookList::list_books() const
{
	return this->m_books;
}