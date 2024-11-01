#pragma once
#include <vector>
#include <string>

using namespace std;

class BookList
{

public:
	void add_book(const string & book);
	const vector<string>& list_books() const;
	BookList(const string & filename);
	void print_booklist();

private:
	vector<string> m_books;
};

