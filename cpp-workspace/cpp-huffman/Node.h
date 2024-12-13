#pragma once

class Node {
    private:
    int m_freq;
    char m_data;

    public:
    Node(int freq, char data);
    ~Node();

    void setFreq(int freq);
    int getFreq() const;
    char getData() const;
};