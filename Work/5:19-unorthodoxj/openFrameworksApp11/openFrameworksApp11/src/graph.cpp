#include "graph.h"

graph::graph()
{

}

// initialize vector >
graph::graph(int row, int col)
{
	r = row;
	c = col;
	adj_list.resize(row*col);
	visited.resize(row*col);
	all_path.resize(row*col * 10);
	for (int i = 0; i < row*col; i++)
		visited[i] = FALSE;
	path_num = 0;
	end_flag = 0;
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

void graph::dfs_computation(int index)
{
	s.push(index);
	all_path[path_num] = index;
	path_num++;
	visited[index] = TRUE;
	printf("push: %d\n", index);

	if (index == node_num - 1) {
		end_flag = 1;
		return;
	}

	for (int i = 0; i < adj_list[index].size(); i++) {
		int j = adj_list[index][i];

		if (end_flag)
			return;
		if (visited[j] == FALSE) {
			dfs_computation(j);
		}
	}

	if (end_flag)
		return;
	printf("pop: %d\n", s.top());
	s.pop();
	all_path[path_num] = s.top();
	path_num++;
}

void graph::dfs_print() {
	vector<int> tmp;
	tmp.resize(adj_list.size());

	int i = 0;
	while (!s.empty()) {
		tmp[i] = s.top();
		s.pop();
		i++;
	}
	dfs_num = i;
	shortest.resize(i);
	printf("dfs: ");
	for (int j = 0; j < i; j++) {
		shortest[j] = tmp[i - j - 1];
		printf("%d ", shortest[j]);
	}

	all_path.resize(path_num);
	printf("\nall path: ");
	for (int j = 0; j < path_num; j++)
		printf("%d ", all_path[j]);
}

void graph::draw_dfs(float sx, float sy) {
	ofSetColor(sp);
	ofSetLineWidth(8);

	float start_x, start_y;

	start_x = sx + sx / 2;
	start_y = sy + sy / 2;

	float prev_x = start_x;
	float prev_y = start_y;
	float cur_x = start_x;
	float cur_y = start_y;

	for (int i = 0; i < shortest.size(); i++) {
		int x = shortest[i] % c;
		int y = shortest[i] / c;

		cur_x = start_x + x * sx;
		cur_y = start_y + y * sy;

		ofDrawLine(prev_x, prev_y, cur_x, cur_y);

		prev_x = cur_x;
		prev_y = cur_y;

	}
}

void graph::draw_path(float sx, float sy) {
	ofSetColor(path);
	ofSetLineWidth(5);

	float start_x, start_y;

	start_x = sx + sx / 2;
	start_y = sy + sy / 2;

	float prev_x = start_x;
	float prev_y = start_y;
	float cur_x = start_x;
	float cur_y = start_y;

	for (int i = 0; i < all_path.size(); i++) {
		int x = all_path[i] % c;
		int y = all_path[i] / c;

		cur_x = start_x + x * sx;
		cur_y = start_y + y * sy;

		ofDrawLine(prev_x, prev_y, cur_x, cur_y);

		prev_x = cur_x;
		prev_y = cur_y;

	}
}

graph::~graph()
{
}
