#pragma once

class Node {
private:
	int m_freq;
	char m_data;
	Node* left;
	Node* right;

public:
	Node(int freq, char data);
	~Node();

	void setLeft(Node* left);
	void setRight(Node* right);
	Node* getLeft();
	Node* getRight();
	void setFreq(int freq);
	int getFreq() const;
	char getData() const;
};