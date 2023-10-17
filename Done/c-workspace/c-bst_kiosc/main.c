#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CODE_LENGTH 6

typedef int itemStock;
typedef struct {
    char itemCode[MAX_CODE_LENGTH];
    itemStock stock;
} item;

typedef struct treeNode {
    item key;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

treeNode* root = NULL;

treeNode* BST_search(treeNode* root, char itemCode[])
{
    if(root == NULL)
        return NULL;
    
    if(strcmp(root->key.itemCode, itemCode) == 0)
        return root;
    
    else if(strcmp(root->key.itemCode, itemCode) < 0)
        return BST_search(root->left, itemCode);
    else
        return BST_search(root->right, itemCode);
}

treeNode* BST_insert(treeNode* root, char itemCode[], itemStock stock)
{
    treeNode* tmp = BST_search(root, itemCode);
    if (tmp == NULL) {
        if(root == NULL)
        {
            root = (treeNode*)malloc(sizeof(treeNode));
            root->left = root->right = NULL;
            for(int i = 0; i < MAX_CODE_LENGTH; i++)
                root->key.itemCode[i] = itemCode[i];
            root->key.stock = stock;
            
            return root;
        }
        else
        {
            if(strcmp(root->key.itemCode, itemCode) < 0)
                root->left = BST_insert(root->left, itemCode, stock);
            else
                root->right = BST_insert(root->right, itemCode, stock);
        }
        return root;
    } else {
        tmp->key.stock += stock;
        return root;
    }
}
treeNode* findMintreeNode(treeNode* root)
{
    treeNode* tmp = root;
    while(tmp->right != NULL)
        tmp = tmp->right;
    return tmp;
}
treeNode* BST_delete(treeNode* root, char itemCode[], itemStock stock)
{
    treeNode* tmp = NULL;
    if(root == NULL)
        return NULL;

    if(strcmp(root->key.itemCode, itemCode) < 0)
        root->left = BST_delete(root->left, itemCode, stock);
    else if(strcmp(root->key.itemCode, itemCode) > 0)
        root->right = BST_delete(root->right, itemCode, stock);
    else
    {
        if (root->key.stock-stock <= 0){
            if(root->right != NULL && root->left != NULL)
            {
                tmp = findMintreeNode(root->left);
                root->key = tmp->key;
                root->left = BST_delete(root->left, itemCode, stock);
            }
            else
            {
                tmp = (root->left == NULL) ? root->right : root->left;
                free(root);
                return tmp;
            }
        } else {
            root->key.stock -= stock;
        }
    }

    return root;
}

void BST_print(treeNode* root)
{
    if(root == NULL)
        return;

    printf("%s %d \n", root->key.itemCode, root->key.stock);
    BST_print(root->left);
    BST_print(root->right);
}

int main()
{
    int cmd = -1;
    
    char itemCode[MAX_CODE_LENGTH];
    int stock;
    
    while (1) {
        printf("0: 종료\n1: 검색\n2: 삽입\n3: 삭제\n4: 출력\n");
        printf("메뉴을 선택하세요: ");
        scanf("%d", &cmd);
        
        switch (cmd) {
            case 0:
                return 0;
                
            case 1:
                printf("재고를 확인 할 키 값을 입력하세요: ");
                scanf("%s", itemCode);
                
                treeNode *t = BST_search(root, itemCode);
                printf("관리번호:%s 재고수량: %d\n", t->key.itemCode, t->key.stock);
                break;
                
            case 2:
                printf("입고할 키 값과 수량을 입력하세요: ");
                scanf("%s", itemCode);
                scanf("%d", &stock);
                
                root = BST_insert(root, itemCode, stock);
                break;
                
            case 3:
                printf("출고할 키 값과 수량을 입력하세요: ");
                scanf("%s", itemCode);
                scanf("%d", &stock);
                
                root = BST_delete(root, itemCode, stock);
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
