#pragma once

#include "ofMain.h"

class graph
{
public:

	int node_num;

	vector<vector<int>> adj_list; // use adjacent list for graph representation

	ofColor path;
	ofColor sp;

	graph(int row, int col);

	void put_edge(int u, int v);
	void print_adj();

	graph();
	~graph();

};

