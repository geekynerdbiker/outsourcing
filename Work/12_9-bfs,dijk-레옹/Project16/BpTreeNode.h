#pragma once
#include "VaccinationData.h"
class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;
	bool bIsLeap;

public:
	BpTreeNode()
		: bIsLeap(true),pParent(nullptr), pMostLeftChild(nullptr)
	{
	}
	virtual ~BpTreeNode() {}
	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }
	void setIsLeap(bool leap) { bIsLeap = leap; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

	bool getIsLeap() const { return bIsLeap; }
//---------------------------Virtual----------------------------------
	virtual void insertDataMap(string n, VaccinationData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}

	virtual map<string, BpTreeNode*>* getIndexMap() { map<string, BpTreeNode*> m; return &m; }
	virtual map<string, VaccinationData*> *getDataMap() { map<string, VaccinationData*> m; return &m; }

	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }
};