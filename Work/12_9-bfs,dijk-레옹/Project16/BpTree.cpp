#include "BpTree.h"
#include <fstream>
#include <cmath>
bool BpTree::Insert(VaccinationData* newData){ //true ���Լ��� false ���Խ���

	string findName = newData->GetUserName();

	if (searchDataNode(findName) == nullptr) //��带 ã������, �� ���� �־������
	{
	
		if (root == nullptr)
		{
			BpTreeDataNode* dataNode = new BpTreeDataNode;

			dataNode->insertDataMap(findName, newData);
			root = dataNode;
			root->setMostLeftChild(root);

	
			return true;
		}
		else
		{
			BpTreeNode* leapNode = root->getMostLeftChild();
			BpTreeNode* prevNode = nullptr;
			map<string, VaccinationData*>* nodeMap = nullptr;
			
			
			while (leapNode != nullptr)
			{
				nodeMap = leapNode->getDataMap();

				if (findName <= (*nodeMap).begin()->first) // ���� �ڸ��� ã�����, ���� �ڵ� �����̴� ó���͸� ��
				{
					if(prevNode == nullptr)
						nodeMap->insert(make_pair(findName, newData));
					else
						prevNode->getDataMap()->insert(make_pair(findName, newData));


					if (nodeMap->size() == order) //�����÷ο� �߻��� ���
						splitDataNode(leapNode);

					return true;
				}
				prevNode = leapNode;
				leapNode = leapNode->getNext();
				if (leapNode == nullptr)	// �� ���Ҵµ� ���� �ڸ� ���� ���, ���� ����
				{
					nodeMap->insert(make_pair(findName, newData));

					if (nodeMap->size() == order) //�����÷ο� �߻��� ���
						splitDataNode(prevNode);

					return true;
				}
			}
			
			if (nodeMap->size() == order) //�����÷ο� �߻��� ���
				splitDataNode(leapNode);
			return true;
		}
	}
	else //��尡 �̹� ����
		return false;
}
BpTreeNode * BpTree::searchDataNode(string n) {
	
	if( root == nullptr) // Ʈ���� ���� ���
		return nullptr;
	else
	{
		BpTreeNode* leapNode = root;		//��Ʈ���� �� ����
		while (leapNode != nullptr) 
		{
			if (leapNode->getIsLeap() == true)	// �����ͳ����
			{
				map<string, VaccinationData*>* nodeMap = leapNode->getDataMap();
				auto it = (*nodeMap).find(n);
				if (it != (*nodeMap).end())	//�ߺ��� ���
					return leapNode;
				for (auto iter : *nodeMap)
				{
					if (n == iter.first)
						return leapNode;
				}
				leapNode = leapNode->getNext();
			}
			else  //�ε��� �����
			{
				map<string, BpTreeNode*>* nodeMap = leapNode->getIndexMap();

				if (n < nodeMap->begin()->first) //ũ�� �ڽ���
					leapNode = nodeMap->begin()->second;
				else //������ ��������
					leapNode = leapNode->getMostLeftChild();
			}

		}
		return nullptr;					//�˻��ߴµ�, ���� ���
	}
	
}
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	//pDataNode ���� ������ ���
	map<string, VaccinationData*>* pMap = pDataNode->getDataMap();

	int splitIdx = ceil((order - 1) / 2.0) + 1;
	int mapIdx = 0;

	//������ ��尡 ���ø��� �Ǵ� ����, �����ͳ�尡 �������� ���� �����ͳ��, ������ �����ͳ�� �׸��� �̵��� �ڽ����� ������ �ε��� ��尡 ����ϴ�.
	//������ ������ �� ������ ���� �����ͳ�尡 ���� ������ ��� ������ �ϰ�, ������ ������ ������ ���� �ε��� ���� ���� �������ݴϴ�.
	//�Ʒ� �ݺ����� ������ ������ �����ͳ�尡 ���� �����͸� ���� ���� ���� ������ ��忡 ���� �й��ϰ�, �й��� ���� �����ݴϴ�.

	BpTreeDataNode* dataNode = new BpTreeDataNode;	//���ø��� �̾��� ���� ������ ���
	for (auto it = (*pMap).begin(); it != (*pMap).end(); )		//pMap�� ���� ����Ű�� �־ �� ó������ ������ ��ȯ�ϴ� ���Դϴ�.
	{
		if (mapIdx >= splitIdx - 1)
		{
			dataNode->insertDataMap(it->first, it->second);
			pDataNode->getDataMap()->erase(it++);
		}
		else
			++it;
		++mapIdx;
	}

	//���� ������ ��尡 ���� ��������, �������(���� ������ ���)�� �̾��ݴϴ�.
	//���� next prev �̾��ֱ�
	dataNode->setNext(pDataNode->getNext());
	if (pDataNode->getNext() != nullptr)
		pDataNode->getNext()->setPrev(dataNode);

	dataNode->setPrev(pDataNode);
	pDataNode->setNext(dataNode);

	BpTreeIndexNode* indexNode = new BpTreeIndexNode;	//�ö� �ε��� ���, ��� �ø��� �Ʒ� �� data ��� ����
	indexNode->setMostLeftChild(pDataNode);	// ������ ���
	map<string, VaccinationData*>* dataMap = dataNode->getDataMap();
	indexNode->insertIndexMap(dataMap->begin()->first, dataNode); //�ڽ� ���

	dataNode->setParent(indexNode);
	pDataNode->setParent(indexNode);

	if (pDataNode == root)
		root = indexNode;

	//Print();
	if (exceedIndexNode(indexNode))			//�ε��� ��带 �����ߴµ�, �ε��� ���ø��� �� �Ͼ ���
		splitIndexNode(indexNode);

	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	map<string, BpTreeNode*>* pMap = pIndexNode->getIndexMap();

	int mapIdx = 0;

	if (pIndexNode->getParent() == nullptr)
	{
		//pIndexNode �����ε���
		BpTreeIndexNode* parentIndexNode = new BpTreeIndexNode;	//�θ� �ε���
		BpTreeIndexNode* rightIndexNode = new BpTreeIndexNode;  //���� �ε���
		
		for (auto it = (*pMap).begin(); it != (*pMap).end(); )
		{
			if (mapIdx == 0)			// ���� �ε��� ���� �״�� ���ֵ� �ȴ�. mostLeft�� �ڽĳ�尡 ������ �ʿ����.
				continue;
			else if (mapIdx == 1)
			{
				rightIndexNode->setMostLeftChild(it->second);		//�������� �ö�(�θ�) ��忡 �ڽ��� ���������� ������.
				parentIndexNode->insertIndexMap(it->first, rightIndexNode); //�θ���� �߰��� �ִ� ���ڿ��� �ε����� �ް�, �ڽĳ��� �������� ������.
			
				parentIndexNode->setMostLeftChild(pIndexNode);				//�θ����� �������

				pIndexNode->setParent(parentIndexNode);						//�θ���
				rightIndexNode->setParent(parentIndexNode);
			}
			else
			{
				rightIndexNode->insertIndexMap(it->first, it->second);	//��������� �ڽĳ��� ������ ����.
				it->second->setParent(rightIndexNode);					//�ڽĳ����� �θ����� �ٲ��ش�.
			}
		}


	}
	else
	{
		//pIndexNode �����ε���
		BpTreeNode* parentIndexNode = pIndexNode->getParent(); 	//�θ� �ε���
		BpTreeIndexNode* rightIndexNode = new BpTreeIndexNode;  //���� �ε���

		for (auto it = (*pMap).begin(); it != (*pMap).end(); )
		{
			if (mapIdx == 0)			// ���� �ε��� ���� �״�� ���ֵ� �ȴ�. mostLeft�� �ڽĳ�尡 ������ �ʿ����.
				continue;
			else if (mapIdx == 1)
			{
				rightIndexNode->setMostLeftChild(it->second);		//�������� �ö�(�θ�) ��忡 �ڽ��� ���������� ������.
				parentIndexNode->insertIndexMap(it->first, rightIndexNode); //�θ���� �߰��� �ִ� ���ڿ��� �ε����� �ް�, �ڽĳ��� �������� ������.
				
				parentIndexNode->setMostLeftChild(pIndexNode);

				pIndexNode->setParent(parentIndexNode);
				rightIndexNode->setParent(parentIndexNode);

				if (exceedIndexNode(parentIndexNode))
					splitIndexNode(parentIndexNode);
			}
			else
			{
				rightIndexNode->insertIndexMap(it->first, it->second);	//��������� �ڽĳ��� ������ ����.
				it->second->setParent(rightIndexNode);					//�ڽĳ����� �θ����� �ٲ��ش�.
			}
		}
	}

	if (pIndexNode == root)
		root = pIndexNode;
	return;
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode) {
	return pDataNode->getDataMap()->size() == 3 ? true : false;

}

bool BpTree::exceedIndexNode(BpTreeNode* pIndexNode) {
	return pIndexNode->getIndexMap()->size() == 3 ? true : false;

}

void BpTree::SearchRange(string start, string end) {

	BpTreeNode* leapNode = root->getMostLeftChild();
	BpTreeNode* prevNode = nullptr;
	map<string, VaccinationData*>* nodeMap = nullptr;

	ofstream out("log.txt", ios::app);

	bool isFirst = false;
	while (leapNode != nullptr)
	{
		nodeMap = leapNode->getDataMap();

		for (auto& el : *nodeMap)
		{
			if (el.first > end)
				break;
			else if (start <= el.first)
			{
				if (isFirst == false)
				{
					out << "======SEARCH_BP=======" << endl;
					isFirst = true;
				}
				out << el.second->GetUserName() << " " << el.second->GetVaccineName() << " " << el.second->GetTimes() << " " << el.second->GetAge() << " " << el.second->GetLocationName() << endl;
			}
		}

		leapNode = leapNode->getNext();
	}

	if (isFirst == true)
		out << "======================" << endl << endl;
	else                 //�����Ͱ� ���� ���
	{
		out << "========ERROR========" << endl;
		out << "400" << endl;
		out << "=====================" << endl << endl;
	}
}

void BpTree::Print() {

	ofstream out("log.txt", ios::app);
	if (root == nullptr)
	{
		out << "========ERROR========" << endl;
		out << "700" << endl;
		out << "=====================" << endl << endl;
		return;
	}

	BpTreeNode* leapNode = root->getMostLeftChild();
	BpTreeNode* prevNode = nullptr;
	map<string, VaccinationData*>* nodeMap = nullptr;
	bool isFirst = false;
	while (leapNode != nullptr)
	{
		nodeMap = leapNode->getDataMap();

		for (auto& el : *nodeMap)
		{
			if (isFirst == false)
			{
				out << "=======PRINT_BP========" << endl;
				isFirst = true;
			}
			out << el.second->GetUserName() << " " << el.second->GetVaccineName() << " " << el.second->GetTimes() << " " << el.second->GetAge() << " " << el.second->GetLocationName() << endl;
		}

		leapNode = leapNode->getNext();
	}
	if (isFirst == true)
		out << "======================" << endl << endl;
}

BpTree::~BpTree()
{
	deleteTree(root);
}

void BpTree::deleteTree(BpTreeNode* curNode)			//Ʈ�� ����
{
	if (curNode == nullptr)
		return;
	if (curNode->getIsLeap() == true)					//���� ����
	{
		delete curNode;
		return;
	}

	deleteTree(curNode->getMostLeftChild());

	delete curNode;										//��ü ���� (������� ������ �Ҹ��ڿ��� ����)
	root = nullptr;
	return;
}