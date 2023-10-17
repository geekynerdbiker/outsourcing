#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    char color;
    struct TreeNode *left, *right, *parent;
}TreeNode;

typedef struct
{
    TreeNode *root;
}TreeType;

TreeNode *Nil;

void init(TreeType *T)
{
    Nil = (TreeNode *)malloc(sizeof(TreeNode));
    Nil->color = 'B';
    T->root = Nil;
}

TreeNode* createNode(int key)
{
    TreeNode* node = (TreeNode *)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = node->right = node->parent = Nil;
    node->color = 'R';
    return node;
}

void leftRotate(TreeType *T, TreeNode *x)
{
    TreeNode *y = x->right;
    x->right = y->left;
    
    if(y->left != Nil)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if(x->parent == Nil)
        T->root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void rightRotate(TreeType *T, TreeNode *x)
{
    TreeNode *y = x->left;
    x->left = y->right;
    
    if(y->right != Nil)
        y->right->parent = x;
    
    y->parent = x->parent;
    
    if(x->parent == Nil)
        T->root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    
    y->right = x;
    x->parent = y;
}

void insertFixup(TreeType *T, TreeNode *z)
{
    TreeNode *y;
    
    while(z->parent->color == 'R')
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if(y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(T, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if(y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(T, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(T, z->parent->parent);
            }
        }
    }
    
    T->root->color = 'B';
}

void insert(TreeType* T, int key)
{
    TreeNode *y = Nil;
    TreeNode *x = T->root;
    TreeNode *z = createNode(key);
    
    while(x != Nil)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;
    
    if (y == Nil)
    {
        T->root = z;
        T->root->color = 'B';
    }
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
    insertFixup(T, z);
}

void preOrder(TreeNode* root)
{
    if(root != Nil)
    {
        printf("[%d(%c)] ", root->key, root->color);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void deleteFixup(TreeType *T, TreeNode *x)
{
    TreeNode *y;
    // x 노드의 색이 검은색 또는 x가 루트가 아닐 때
    while (x!= Nil && x != T->root && x->color == 'B') {
        // x가 왼쪽 자식일 때
        if (x == x->parent->left) {
            // y에 오른쪽 자식 대입
            y = x->parent->right;
            
            // 오른쪽 자식이 빨간색일 경우
            if (y->color == 'R') {
                // 검은색으로 변경 후, 부모 노드를 빨간색으로 변경
                y->color = 'B';
                x->parent->color = 'R';
                // 왼쪽으로 회전 후 오른쪽 노드로 지정
                leftRotate(T, x->parent);
                y = x->parent->right;
            }
            
            // y의 자식이 모두 검은색일 경우
            if (y->left->color =='B' && y->right->color == 'B') {
                // 본인의 색을 빨간색으로 변경 후, 부모노드로 이동
                y->color = 'R';
                x = x->parent;
            } else {
                // 오른쪽 자식만 검은 색일 때
                if (y->right->color == 'B') {
                    // 왼쪽 자식도 검은색으로 칠하고 스스로를 빨간색으로 색칠
                    y->left->color = 'B';
                    y->color = 'R';
                    // 오른쪽으로 회전 후 왼쪽 노드로 지정
                    rightRotate(T, y);
                    y = x->parent->left;
                }
                
                y->color = x->parent->color;
                x->parent->color = 'B';
                y->right->color = 'B';
                leftRotate(T, x->parent);
                x = T->root;
            }
            // 오른쪽 자식일 때 (왼쪽 자식일 때와 방향만 반대로 같은 동작 실행)
        } else {
            y = x->parent->left;
            
            if (y->color == 'R') {
                y->color = 'B';
                x->parent->color = 'R';
                rightRotate(T, x->parent);
                y = x->parent->left;
            }
            
            if (y->right->color =='B' && y->left->color == 'B') {
                y->color = 'R';
                x = x->parent;
            } else {
                if (y->left->color == 'B') {
                    y->right->color = 'B';
                    y->color = 'R';
                    leftRotate(T, y);
                    y = x->parent->left;
                }
                y->color = x->parent->color;
                x->parent->color = 'B';
                y->left->color = 'B';
                rightRotate(T, x->parent);
                x = T->root;
            }
        }
        // 블랙으로 변경
        x->color = 'B';
    }
}

// 삭제할 노드의 위치를 대체할 노드 산출
TreeNode* treeMinimum(TreeType* T, TreeNode* z) {
    // 루트가 Nil이면
    if (T->root == Nil)
        // NULL 반환
        return NULL;
    
    // 트리 노드 포인터 지정.
    TreeNode *tp = z;
    
    // 왼쪽 노드가 Nil이 아닌동안, 왼쪽으로 이동 -> 끝값 찾음
    while (tp->left != Nil)
        tp = tp->left;
    
    // 최소값 반환
    return tp;
}

//노드 이식 함수
void transplant(TreeType* T, TreeNode* u, TreeNode* v) {
    // u -> 삭제할 노드, v -> 대체할 노드
    // 삭제할 노드가 루트인 경우
    if (u->parent == Nil) {
        // 루트를 v로 설정
        T->root = v;
        // 삭제할 노드가 부모 왼쪽 자식일 때
    } else if (u == u->parent->left) {
        u->parent->left = v;
        // 삭제할 노드가 부모 오른쪽 자식일 때
    } else
        u->parent->right = v;
    // 삭제할 노드의 부모노드를 대체할 노드의 부모 노드로 지정
    v->parent = u->parent;
}

// 노드를 실질적으로 삭제하는 함수.
void deleteNode(TreeType *T, TreeNode *z) {
    // 삭제할 타겟 노드를 y에 저장.
    TreeNode* y = z;
    int yOriginalColor = y->color;
    
    TreeNode* x;
    // 왼쪽 자식이 없을 때
    if (z->left == Nil) {
        // x에 오른쪽 자식 설정 후 삭제할 노드에 이식
        x = z->right;
        transplant(T, z, z->right);
        // 오른쪽 자식이 없을 때
    } else if (z->right == Nil) {
        // x에 왼쪽 자식 설정 후 삭제할 노드에 이식
        x = z->left;
        transplant(T, z, z->left);
        // 자식이 둘 다 있을 때
    } else {
        // y에 오른쪽 자식을 기준으로 트리 최소값 탐색 후 정보 저장
        y = treeMinimum(T, z->right);
        yOriginalColor = y->color;
        x = y->right;
        
        // y의 부모가 삭제할 노드일 때
        if (y->parent == z) {
            // 부모 노드 변경
            x->parent = y;
        } else {
            // 오른쪽 자식을 이식
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        // 왼쪽 자식을 이식
        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    // 삭제할 노드의 색상이 검은색일때
    if (yOriginalColor == 'B')
        deleteFixup(T, x);
}

// 노드를 찾는 함수.
// Nil 노드가 아닌 동안 순회하며 찾으면 해당 노드, 그렇지 않으면 Nil 노드 반환.
// key값을 통해 해당 키를 가진 노드를 찾기 위함.
TreeNode *findNode(TreeType *T, int key) {
    TreeNode* tp = T->root;
    
    while (tp != Nil) {
        if (tp->key > key)
            tp = tp->left;
        else if (tp->key < key)
            tp = tp->right;
        else
            return tp;
    }
    return Nil;
}

// 주로 사용할 삭제 함수.
// 키 값을 넘겨받아 해당 키를 가진 노드를 찾아서 노드 삭제 함수 호출
void delete(TreeType *T, int key) {
    deleteNode(T, findNode(T, key));
}

int main(void)
{
    TreeType T;
    init(&T);
    
    insert(&T, 8);
    insert(&T, 7);
    insert(&T, 12);
    insert(&T, 3);
    insert(&T, 6);
    insert(&T, 4);
    insert(&T, 5);
    insert(&T, 10); preOrder(T.root); printf("\n");
    
    delete(&T, 12);
    delete(&T, 4);
    delete(&T, 6);
    delete(&T, 10); preOrder(T.root); printf("\n");
    
    return 0;
}
