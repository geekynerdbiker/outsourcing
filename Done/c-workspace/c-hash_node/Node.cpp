#include "Node.h"

Node::Node(int freq , char data) {
	m_freq = freq;
	m_data = data;
	left = nullptr;
	right = nullptr;
}

Node::~Node() {
	delete left;
	delete right;
}


void Node::setLeft(Node* left) {
	this->left = left;
}

void Node::setRight(Node* right) {
	this->right = right;
}

Node* Node::getLeft() {
	return left;
}
Node* Node::getRight() {
	return right;
}

void Node::setFreq(int freq) {
	m_freq = freq;
}

int Node::getFreq() const {
	return m_freq;
}

char Node::getData() const {
	return m_data;
}