#include <cstdio>
#include <vector>
#include <algorithm>
#pragma once

using namespace std;

struct Edge{
    int f, t, w;
    Edge(){}
    Edge(int f, int t, int w) {
        this->f = f;
        this->t = t;
        this->w = w;
    }
};

vector<Edge> m(3002);

int parent[3002];
int level[3002];
int N, M, sizeHeap;

int find(int x) {
    if (x == parent[x]) return x;
    
    return parent[x] = find(parent[x]);
}

bool unionHeap(int a, int b){
    a = find(a);
    b = find(b);
    
    if (a == b) return false;
    
    if (level[a] > level[b]) swap(a,b);
    
    parent[a] = b;
    level[b] += level[a];
    level[b] = 1;
    
    return true;
}

void updateHeap(int node) {
    if (node*2+1 >= sizeHeap) return;
    if (m[node*2].w == 0 && m[node*2+1].w == 0) return;

    int index = node;
    int temp = m[node].w;
    int left = m[node*2].w;
    int right = m[node*2+1].w;
    
    if (left && temp > left) {
        index = node * 2;
        temp = left;
    } if (right && temp > right) {
        index = node * 2 + 1;
        temp = right;
    } if (node != index) {
        swap(m[node],m[index]);
        updateHeap(index);
    }
    if i == NULL
}

void myHeapify() {
    for (int i = M; i >= 1; i--)
        updateHeap(i);
}

Edge myDeleteMin() {
    Edge result = m[1];
    
    m[1] = m[sizeHeap];
    m[sizeHeap].f = 0;
    m[sizeHeap].t = 0;
    m[sizeHeap].w = 0;
    
    sizeHeap--;
    updateHeap(1);
    
    return result;
}

int readGraph() {
    int result = 0;
    
    for (int i = 1; i <= M; i++) {
        Edge curr = myDeleteMin();
        
        int f = curr.f;
        int t = curr.t;
        int w = curr.w;
        
        if (unionHeap(f, t)) result += w;
    }
    return result;
}

int main() {
    scanf("%d %d",&N, &M);
    sizeHeap = M;
    m.resize(M*2+2);
    
    for (int i = 0; i < N; i++) {
        level[i] = 1;
        parent[i] = i;
    }
    
    for (int i = 1; i <= M; i++) {
        int f, t, w;
        scanf("%d %d %d", &f, &t, &w);
        m[i] = Edge(f, t, w);
    }
    
    myHeapify();
    printf("%d\n", readGraph());
    
    return 0;
}
