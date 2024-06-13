#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int vertex;
    int weight;
} Edge;

typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    int* position;
    MinHeapNode** array;
} MinHeap;

MinHeapNode* newMinHeapNode(int vertex, int distance) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = vertex;
    minHeapNode->distance = distance;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->position = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->distance < minHeap->array[smallest]->distance) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->distance < minHeap->array[smallest]->distance) {
        smallest = right;
    }

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->position[smallestNode->vertex] = idx;
        minHeap->position[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->position[root->vertex] = minHeap->size - 1;
    minHeap->position[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int vertex, int distance) {
    int i = minHeap->position[vertex];
    minHeap->array[i]->distance = distance;

    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance) {
        minHeap->position[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->position[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* minHeap, int vertex) {
    return minHeap->position[vertex] < minHeap->size;
}

void printArr(int dist[], int n, int prev[]) {
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        if (prev[i] == -1)
            fprintf(outputFile, "%d\t%d\tNIL\n", i, dist[i]);
        else
            fprintf(outputFile, "%d\t%d\t%d\n", i, dist[i], prev[i]);
    }

    fclose(outputFile);
}

void dijkstra(int V, int** graph, int src) {
    int* dist = (int*)malloc(V * sizeof(int));
    int* prev = (int*)malloc(V * sizeof(int));

    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->position[v] = v;
        prev[v] = -1;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->position[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && isInMinHeap(minHeap, v) && dist[u] != INT_MAX && graph[u][v] + dist[u] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }

    printArr(dist, V, prev);

    free(dist);
    free(prev);
    free(minHeap->position);
    free(minHeap->array);
    free(minHeap);
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    int V, E, src;
    fscanf(inputFile, "%d\t%d\t%d", &V, &E, &src);

    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++) {
        int u, v, weight;
        fscanf(inputFile, "%d\t%d\t%d", &u, &v, &weight);
        graph[u][v] = weight;
    }

    fclose(inputFile);

    dijkstra(V, graph, src);

    for (int i = 0; i < V; ++i) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
