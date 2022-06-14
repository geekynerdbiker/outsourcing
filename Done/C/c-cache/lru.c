//
//  main.c
//  cache
//
//  Created by Jacob An on 2021/12/22.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_BUFFER 8192

typedef struct cache_buffer
{
    int key, height, fifoOrder, lruOrder;
    struct cache_buffer* left, *right;
}Cache_Buffer;

int fifo[MAX_BUFFER] = {0,}, lru[MAX_BUFFER] = {0,};
int fifoIndex = 0, lruIndex = 0, totalIndex = 0, hit = 0, ref = 0;

int searchLRUNode();
int getBalance(Cache_Buffer* N);

void searchOldNode(Cache_Buffer *root);

Cache_Buffer* newNode(int key);
Cache_Buffer* leftRotate(Cache_Buffer* x);
Cache_Buffer* rightRotate(Cache_Buffer* y);
Cache_Buffer* LRU(Cache_Buffer *root, int key);
Cache_Buffer* FIFO(Cache_Buffer *root, int key);
Cache_Buffer* insert(Cache_Buffer* node, int key);
Cache_Buffer* deleteNode(Cache_Buffer* root, int order);


// 두 값 비교하여 최댓값 리턴
int max(int a, int b) {
    return (a > b) ? a : b;
}

// ATL 트리 높이를 리턴
int height(Cache_Buffer* N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


// 새 노드 생성
Cache_Buffer* newNode(int key)
{
    Cache_Buffer* node = (Cache_Buffer*)malloc(sizeof(Cache_Buffer));
    
    node->key = key;
    node->height = 1;  // 새 노드는 항상 리프 노드
    node->fifoOrder = totalIndex++;
    node->lruOrder = lruIndex;
    node->left = NULL;
    node->right = NULL;
    
    fifo[fifoIndex++]++;
    
    return(node);
}

// 가장 오래된 노드 인덱스 탐색
void searchOldNode(Cache_Buffer *root)
{
    int index = -1;
    
    for (int i=1; i < MAX_BUFFER; i++) {
        for (int j=0; j < MAX_BUFFER; j++){
            if (fifo[j] <= i) {
                fifoIndex = j;
                return;
            }
            i = fifo[j];
        }
    }
}

// First In First Out
Cache_Buffer* FIFO(Cache_Buffer *root, int key)
{
    // 가득 찼으면, 가장 오래된 노드 삭제
    if(totalIndex >= MAX_BUFFER) {
        searchOldNode(root);
        deleteNode(root, fifoIndex);
    }
    
    // 새 노드 삽입
    root = insert(root, key);
    
    return root;
}

// 가장 마지막에 사용된 인덱스 탐색
int searchLRUNode()
{
    int minimum = 2147483647, minIndex = 0;
    
    for (int i=1; i < MAX_BUFFER; i++) {
        if (lru[i] < minimum) {
            minimum = lru[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Least Recently Used
Cache_Buffer* LRU(Cache_Buffer *root, int key)
{
    // LRU 실행 시 오버플로우 방지
    if (fifoIndex >= MAX_BUFFER) fifoIndex = 0;
    // 가득 찼으면, 가장 오래된 노드 삭제
    if( totalIndex >= MAX_BUFFER) {
        int minIndex = searchLRUNode();
        deleteNode(root, minIndex);
    }
    
    // 새 노드 삽입
    root = insert(root, key);
    
    return root;
}

// 서브트리 오른쪽 회전
Cache_Buffer* rightRotate(Cache_Buffer* y)
{
    Cache_Buffer* x = y->left;
    Cache_Buffer* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // 높이 최신화
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // 새로운 루트 리턴
    return x;
}

// 서브트리 왼쪽 회전
Cache_Buffer* leftRotate(Cache_Buffer* x)
{
    Cache_Buffer* y = x->right;
    Cache_Buffer* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// 노드 N의 밸런스 계산 후 리턴
int getBalance(Cache_Buffer* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// 트리에 새 노드 삽입
Cache_Buffer* insert(Cache_Buffer* node, int key)
{
    // 일반적인 경우
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else {
        // 히트
        
        hit++;
        return node;
    }
        

    // 부모 노드의 높이 최신화
    node->height = 1 + max(height(node->left),
        height(node->right));

    // 부모 노드의 밸런스 값을 얻어 올바른지 확인
    int balance = getBalance(node);


    // 밸런스가 맞지 않을 때
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 트리에서 최솟값을 가진 노드 탐색
Cache_Buffer* minValueNode(Cache_Buffer* node)
{
    Cache_Buffer* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}


// 재귀적 노드 삭제
Cache_Buffer* deleteNode(Cache_Buffer* root, int key)
{
    // 일반적인 경우
    if (root == NULL)
        return root;

    // 루트 노드의 값보다 삭제될 노드의 순서가 작을 때
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // 루트 노드의 값보다 삭제될 노드의 순서가 클 때
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            Cache_Buffer* temp = root->left ? root->left :
                root->right;

            // 자식이 없는 경우
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // 자식이 한쪽인 경우
                *root = *temp;
            
            free(temp);
        }
        else
        {
            Cache_Buffer* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }


    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main()
{
    // 빈 트리 생성
    Cache_Buffer* root = NULL;

    // 파일 열기
    FILE *fp = fopen("test_trace.txt", "read");
    
    if (fp == NULL) {
        printf("No file name exist.\n");
        return 0;
    }
    
    int cache;
    char *pLine, line[10];
    
    while (!feof(fp)) {
        pLine = fgets(line, sizeof(line), fp);
        if(pLine != NULL) {
            cache = atoi(pLine);
            root = LRU(root, cache);
//            root = FIFO(root, cache);
            ref++;
        }
    }
    fclose(fp);
    
    double hitRatio = (double)hit / (double)ref;
    printf("hit ratio = %f, miss ratio = %f\n\n", hitRatio, 1-hitRatio);
    printf("total access = %d, hit = %d, miss = %d\n", ref, hit, ref-hit);
    printf("Hit ratio = %f\n", hitRatio);
    return 0;
}
