#include "graph.h"

graph::graph()
{

}

// initialize vector 
graph::graph(int row, int col)
{
	adj_list.resize(row*col);

}

void graph::put_edge(int u, int v)
{
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}

void graph::print_adj()
{
	for (int i = 0; i < node_num; i++) {
		printf("Node %d's connection list\n", i);
		for (int j = 0; j < adj_list[i].size(); j++) {
			cout << adj_list[i][j] << endl;
		}
	}

}

graph::~graph()
{
}
