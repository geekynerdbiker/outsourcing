//
//  main.c
//  bst
//
//  Created by Jacob An on 2022/04/12.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct NodeStruct
{
    int value;
    struct NodeStruct* leftChild;
    struct NodeStruct* rightChild;
}Node;

Node* root = NULL;

Node* BST_insert(Node* root, int value)
{
    if(root == NULL)
    {
        root = (Node*)malloc(sizeof(Node));
        root->leftChild = root->rightChild = NULL;
        root->value = value;
        return root;
    }
    else
    {
        if(root->value > value)
            root->leftChild = BST_insert(root->leftChild, value);
        else
            root->rightChild = BST_insert(root->rightChild, value);
    }
    return root;
}
Node* findMinNode(Node* root)
{
    Node* tmp = root;
    while(tmp->rightChild != NULL)
        tmp = tmp->rightChild;
    return tmp;
}
Node* BST_delete(Node* root, int value)
{
    Node* tNode = NULL;
    if(root == NULL) {
        printf("삭제할 키 값 [%d]은 트리에 없습니다.\n");
        return NULL;
    }

    if(root->value > value)
        root->leftChild = BST_delete(root->leftChild, value);
    else if(root->value < value)
        root->rightChild = BST_delete(root->rightChild, value);
    else
    {
        if(root->rightChild != NULL && root->leftChild != NULL)
        {
            tNode = findMinNode(root->leftChild);
            root->value = tNode->value;
            root->leftChild = BST_delete(root->leftChild, tNode->value);
        }
        else
        {
            tNode = (root->leftChild == NULL) ? root->rightChild : root->leftChild;
            free(root);
            return tNode;
        }
    }

    return root;
}
Node* BST_search(Node* root, int value)
{
    if(root == NULL) {
        printf("찾는 키 값 [%d]는 트리에 없습니다.\n", value);
        return NULL;
    }

    if(root->value == value){
        printf("찾는 키 값 [%d]는 트리에 있습니다.\n", value);
        return root;
    }
    else if(root->value > value)
        return BST_search(root->leftChild, value);
    else
        return BST_search(root->rightChild, value);
}
void BST_print(Node* root)
{
    if(root == NULL)
        return;

    printf("%d ", root->value);
    BST_print(root->leftChild);
    BST_print(root->rightChild);
}

int main()
{
    int cmd = -1, value = -1;
    while (cmd != 0) {
        printf("0: 종료\n1: 검색\n2: 삽입\n3: 삭제\n4: 출력\n");
        printf("메뉴을 선택하세요: ");
        scanf("%d", &cmd);
        
        switch (cmd) {
            case 0:
                return 0;
                
            case 1:
                printf("검색할 키 값을 입력하세요: ");
                scanf("%d", &value);
                
                BST_search(root, value);
                break;
                
            case 2:
                printf("삽입할 키 값을 입력하세요: ");
                scanf("%d", &value);
                
                root = BST_insert(root, value);
                break;
                
            case 3:
                printf("삭제할 키 값을 입력하세요: ");
                scanf("%d", &value);
                
                root = BST_delete(root, value);
                break;
                
            case 4:
                printf("출력 결과>> ");
                BST_print(root);
                printf("\n");
                break;
        }
        printf("\n");
    }
}
