#pragma once
#include <string>
#include <iostream>

using namespace std;

class StringApp {
public:
	StringApp();
    
	void printAlpabets();
	void setFormat();
	void printSentence();

private:
	string input, corr, encoded;
	int gap;
};
