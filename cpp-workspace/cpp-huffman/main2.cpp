#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "Heap.h"

using namespace std;
unordered_map<Node*, pair<Node*, Node*>> children;

void encode(Node* root, const string& str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    auto it = children.find(root);
    if (it == children.end()) {
        huffmanCode[root->getData()] = str;
        return;
    }

    encode(it->second.first, str + "0", huffmanCode);
    encode(it->second.second, str + "1", huffmanCode);
}

Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    Heap heap(100);

    for (auto& p : freq) {
        Node* node = new Node(p.second, p.first);
        heap.push(node);
    }


    while (heap.size() > 1) {
        Node* left = heap.pop();
        Node* right = heap.pop();

        if (left->getFreq() > right->getFreq() ||
            (right->getFreq() == left->getFreq() && right->getData() < left->getData())) {
            swap(left, right);
        }
        
        int combinedFreq = left->getFreq() + right->getFreq();
        char combinedData = min(left->getData(), right->getData());
        Node* parent = new Node(combinedFreq, combinedData);

        children[parent] = { left, right };

        heap.push(parent);
    }

    return heap.pop();
}

void printHuffmanCodes(Node* root, const string& text) {
    if (!root) {
        cout << "No tree built." << endl;
        return;
    }

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    vector<pair<char, string>> vec(huffmanCode.begin(), huffmanCode.end());
    sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        if (a.second.length() != b.second.length())
            return a.second.length() < b.second.length();
        return a.first < b.first;
    });


    for (auto& hc : vec) 
        cout << hc.first << " " << hc.second << "\n";
    
    string encoded;
    for (char ch : text) 
        encoded += huffmanCode[ch];
    
    cout << endl << encoded << endl;
}

int main() {
    string text = "This is an example of a Huffman tree";
    for (auto& ch : text) ch = (char)tolower((unsigned char)ch);

    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;

    Node* root = buildHuffmanTree(freq);
    printHuffmanCodes(root, text);
    return 0;
}
