#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stack>

#define max(a,b)    (((a) > (b)) ? (a) : (b))

bool AVLTree::Insert(VaccinationData* pVac){

	addAVLTree(&root, pVac);
	return false;
}

void AVLTree::GetVector(vector<VaccinationData*>& v) {
	
	stack<AVLNode*> st;
	st.push(root);

	while (!st.empty())
	{
		AVLNode* node = st.top();
		st.pop();
		v.push_back(node->getVacData());

		if (nullptr != node->getLeft())
		{
			st.push(node->getLeft());
		}
		if (nullptr != node->getRight())
		{
			st.push(node->getRight());
		}
	}

	

	/*for (auto iter = v.begin(); iter < v.end(); iter++)
	{
		cout << (*iter)->GetUserName() << endl;
	}*/
}

VaccinationData* AVLTree::Search(string name){
	return  searchAVLTree(root, name)->getVacData();
}

AVLNode* AVLTree::addAVLTree(AVLNode** root, VaccinationData* key)
{
	if (*root == NULL)
	{
		*root = (AVLNode*)malloc(sizeof(AVLNode));
		if (*root == NULL)
		{
			printf("메모리 할당 실패\n");
			exit(-1);
		}
		//생성자에서 null
		(*root)->setVacData(key);
		(*root)->setLeft(NULL);
		(*root)->setRight(NULL);
	}
	else if (key->GetUserName() < (*root)->getVacUserName())
	{
		AVLNode* pLeft = (*root)->getLeft();

		(*root)->setLeft( addAVLTree( &pLeft, key) );
		(*root) = balanceAVLTree(root);
	}
	else if (key->GetUserName() > (*root)->getVacUserName())
	{
		AVLNode* pRight = (*root)->getRight();

		(*root)->setRight( addAVLTree( &pRight , key ));
		(*root) = balanceAVLTree(root);
	}
	else
	{
		printf("\n중복 키로 인한 삽입 실패\n");
		exit(-1);
	}

	return *root;
}

// 균형 트리 만드는 함수
AVLNode* AVLTree::balanceAVLTree(AVLNode** node)
{
	int height_diff = getBalanceValue(*node);

	if (height_diff > 1) // 왼쪽 서브트리 균형 맞추기
	{
		if (getBalanceValue( (*node)->getLeft() ) > 0)
			*node = rotateAVLTreeLL(*node);
		else
			*node = rotateAVLTreeLR(*node);
	}
	else if (height_diff < -1) // 오른쪽 서브트리 균형 맞추기
	{
		if (getBalanceValue((*node)->getRight()) < 0)
			*node = rotateAVLTreeRR(*node);
		else
			*node = rotateAVLTreeRL(*node);
	}
	return *node;
}

AVLNode* AVLTree::rotateAVLTreeLL(AVLNode* parent)
{
	AVLNode* child = parent->getLeft();
	parent->setLeft( child->getRight() );
	child->setRight( parent );
	return child;
}


AVLNode* AVLTree::rotateAVLTreeRR(AVLNode* parent)
{
	AVLNode* child = parent->getRight();
	parent->setRight(child->getLeft());
	child->setLeft(parent);
	return child;
}


AVLNode* AVLTree::rotateAVLTreeRL(AVLNode* parent)
{
	AVLNode* child = parent->getRight();
	parent->setRight( rotateAVLTreeLL(child) );
	return rotateAVLTreeRR(parent);
}

AVLNode* AVLTree::rotateAVLTreeLR(AVLNode* parent)
{
	AVLNode* child = parent->getLeft();
	parent->setLeft( rotateAVLTreeRR(child) );
	return rotateAVLTreeLL(parent);
}

// 트리의 높이 측정 함수
// 순환호출로 각각의 높이를 구하고 이들 중에서 더 큰값에 1을 더하면 트리의 높이가 된다.
int AVLTree::getHeight(AVLNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(getHeight(node->getLeft()), getHeight(node->getRight()));
	return height;
}

// 노드의 균형인수 반환 함수
// 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
int AVLTree::getBalanceValue(AVLNode* node)
{
	if (node == NULL) return 0;
	return getHeight(node->getLeft()) - getHeight(node->getRight());
}

// 탐색 함수
AVLNode* AVLTree::searchAVLTree(AVLNode* node, string name)
{
	if (node == NULL) return NULL;

	//printf("%d->", node->Get);

	if (name == node->getVacUserName())
		return node;
	else if (name < node->getVacUserName())
		return searchAVLTree(node->getLeft(), name);
	else
		return searchAVLTree(node->getRight(), name);
}

