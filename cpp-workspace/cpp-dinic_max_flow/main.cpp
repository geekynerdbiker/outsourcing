#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

const int MAX = 52;
const int INF = 1e9;

int m, c[MAX][MAX], level[MAX], work[MAX];
vector<int> g[MAX];

int src = 0, snk = 0;

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(src);
    level[src] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (level[v] == -1 && c[u][v] > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[snk] != -1;
}

int dfs(int u, int ret) {
    if (u == snk) return ret;
    
    for (int& i = work[u], v; i < g[u].size(); i++) {
        v = g[u][i];
        if (level[v] == level[u] + 1 && c[u][v] > 0) {
            int tmp = dfs(v, min(ret, c[u][v]));
            if (tmp > 0) {
                c[u][v] -= tmp;
                c[v][u] += tmp;
                return tmp;
            }
        }
    }
    return 0;
}

int main() {
    string filename("1.inp");
    string line;
    
    ifstream ifile(filename);
    ofstream ofile("flow.out");
    
    if (!ifile.is_open()) {
        cerr << "Could not open the file - '"
        << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    
    while (getline(ifile, line)) {
        if (snk == 0) {
            snk = atoi(line.c_str()) - 1;
        } else {
            stringstream sstream(line);
            string token;
            
            getline(sstream, token, ' ');
            int i = atoi(token.c_str());
            
            getline(sstream, token, ' ');
            int j = atoi(token.c_str());
            
            getline(sstream, token, ' ');
            int w = atoi(token.c_str());
            
            if (i == -1 || j == -1 || w == -1)
                break;
            
            c[i][j] = c[j][i] += w;
            g[i].push_back(j);
            g[j].push_back(i);
        }
    }
    
    int total = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        int flow;
        while (flow = dfs(src, INF))
            total += flow;
    }
    
    ofile << total << '\n';
    ofile.close();
}
