#include <stdio.h>

#define MAX_VER  15
#define MAX_EDGE 30

typedef struct edge{
    int s,d;
    int w;
    
}EDGE;

struct vertices{
    int p;
    int rank;
    
}

vt[MAX_VER];
EDGE e[MAX_EDGE];

void mst_kruskal( int, int);
void make_set( int);
void union_set( int, int);
int find_set( int);
void sort_edge( int);
void max_heapify( int, int);
void build_max_heap( int);

int main(int argc, const char * argv[]) {
    int nv, ne;
    int i;
    int s, d;
    
    freopen("input.txt", "r", stdin);
    
    scanf("%d%d", &nv, &ne);
    for( i = 0 ; i < ne ; i ++)  {
        scanf("%d%d", &s, &d);
        e[i].s  = s;
        e[i].d  = d;
        scanf("%d", &e[i].w);
    }
    mst_kruskal( nv, ne);
    return 0;
}


void make_set( int v) {
    vt[v].p  = v;
    vt[v].rank  = 0;
}

int find_set( int v){
    if( vt[v].p != v) {
        vt[v].p = find_set( vt[v].p);
    }
    return vt[v].p;
}

void union_set( int v, int u) {
    v = find_set( v);
    u = find_set( u);
    if(vt[v].rank > vt[u].rank) {
        vt[u].p = v;
    } else {
        vt[v].p = u;
        if( vt[v].rank == vt[u].rank) {
            vt[u].rank = vt[u].rank + 1;
        }
    }
}

void mst_kruskal( int nv, int ne) {
    int i;
    int total   = 0;
    for( i = 0 ; i < nv ; i ++) {
        make_set(i);
    }
    sort_edge( ne);
    printf("Kruscal's algorithm을 이용한 minimum cost spanning tree 생성: T={ ");
    for( i = 0  ; i < ne ; i ++) {
        if( find_set( e[i].s) != find_set( e[i].d))  {
            union_set( e[i].s, e[i].d);
            total = total + e[i].w;
            
            printf("(%d,%d) ", e[i].s, e[i].d);
        }
    }
    printf("}\n");
}

void sort_edge( int ne){
    EDGE temp;
    int i;
    build_max_heap( --ne);
    for( i = ne ; i > 0 ; i --) {
        temp = e[i];
        e[i] = e[0];
        e[0] = temp;
        max_heapify( 0, i);
    }
}

void max_heapify( int index, int size){
    EDGE temp;
    
    int left = index * 2 + 1;
    int right   = index * 2 + 2;
    int largest = index;
    if( left < size && e[left].w > e[largest].w) {
        largest = left;
    }  if( right < size && e[right].w > e[largest].w) {
        largest = right;
    } if( largest != index) {
        temp  = e[largest];
        e[largest]  = e[index];
        e[index] = temp;
        max_heapify( largest, size);
    }
}

void build_max_heap( int ne){
    int i;
    for(i = ne/2 ; i >= 0 ; i--){
        max_heapify( i, ne);
    }
}
