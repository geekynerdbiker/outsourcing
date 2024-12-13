#include "Node.h"

Node::Node(int freq, char data) : m_freq(freq), m_data(data) {}
Node::~Node() {}

void Node::setFreq(int freq) {
    m_freq = freq;
}

int Node::getFreq() const {
    return m_freq;
}

char Node::getData() const {
    return m_data;
}
