#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "VaccinationData.h"
#include "AVLNode.h"
/* class AVL */

class AVLTree{
private:
	AVLNode*	root;

public:
	
	AVLTree(){
		root=NULL;
	}
	~AVLTree(){};
	bool		Insert(VaccinationData* pVac);
	VaccinationData*	Search(string name);
	void GetVector(vector<VaccinationData*>& v);

	/// <summary>
	/// 
	/// </summary>
	AVLNode* addAVLTree(AVLNode** root, VaccinationData* key);
	AVLNode* balanceAVLTree(AVLNode** node);
	AVLNode* rotateAVLTreeLL(AVLNode* parent);
	AVLNode* rotateAVLTreeRR(AVLNode* parent);
	AVLNode* rotateAVLTreeRL(AVLNode* parent);
	AVLNode* rotateAVLTreeLR(AVLNode* parent);
	AVLNode* searchAVLTree(AVLNode* node, string name);


	int getHeight(AVLNode* node);
	int getBalanceValue(AVLNode* node);

};

#endif

