#pragma once

#include "ofMain.h"
#include <stack>

class graph
{
public:

	int node_num;
	int path_num;
	int dfs_num;
	int end_flag;
	int r, c;
	vector<vector<int>> adj_list; // use adjacent list for graph representation
	vector<bool> visited;
	vector<int> shortest;
	vector<int> all_path;
	stack<int> s;

	ofColor path;
	ofColor sp;

	graph(int row, int col);

	void put_edge(int u, int v);
	void print_adj();
	void dfs_computation(int index);
	void dfs_print();
	void draw_path(float sx, float sy);
	void draw_dfs(float sx, float sy);

	graph();
	~graph();

};

