#include "BpTree.h"
#include <fstream>
#include <cmath>
bool BpTree::Insert(VaccinationData* newData){ //true 삽입성공 false 삽입실패

	string findName = newData->GetUserName();

	if (searchDataNode(findName) == nullptr) //노드를 찾지못함, 즉 만들어서 넣어줘야함
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

				if (findName <= (*nodeMap).begin()->first) // 넣을 자리를 찾을경우, 맵은 자동 정렬이니 처음것만 비교
				{
					if(prevNode == nullptr)
						nodeMap->insert(make_pair(findName, newData));
					else
						prevNode->getDataMap()->insert(make_pair(findName, newData));


					if (nodeMap->size() == order) //오버플로우 발생한 경우
						splitDataNode(leapNode);

					return true;
				}
				prevNode = leapNode;
				leapNode = leapNode->getNext();
				if (leapNode == nullptr)	// 다 돌았는데 넣을 자리 없는 경우, 끝에 넣음
				{
					nodeMap->insert(make_pair(findName, newData));

					if (nodeMap->size() == order) //오버플로우 발생한 경우
						splitDataNode(prevNode);

					return true;
				}
			}
			
			if (nodeMap->size() == order) //오버플로우 발생한 경우
				splitDataNode(leapNode);
			return true;
		}
	}
	else //노드가 이미 존재
		return false;
}
BpTreeNode * BpTree::searchDataNode(string n) {
	
	if( root == nullptr) // 트리가 없는 경우
		return nullptr;
	else
	{
		BpTreeNode* leapNode = root;		//루트부터 비교 시작
		while (leapNode != nullptr) 
		{
			if (leapNode->getIsLeap() == true)	// 데이터노드라면
			{
				map<string, VaccinationData*>* nodeMap = leapNode->getDataMap();
				auto it = (*nodeMap).find(n);
				if (it != (*nodeMap).end())	//중복일 경우
					return leapNode;
				for (auto iter : *nodeMap)
				{
					if (n == iter.first)
						return leapNode;
				}
				leapNode = leapNode->getNext();
			}
			else  //인덱스 노드라면
			{
				map<string, BpTreeNode*>* nodeMap = leapNode->getIndexMap();

				if (n < nodeMap->begin()->first) //크면 자식쪽
					leapNode = nodeMap->begin()->second;
				else //작으면 좌측노드로
					leapNode = leapNode->getMostLeftChild();
			}

		}
		return nullptr;					//검색했는데, 없는 경우
	}
	
}
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	//pDataNode 기존 데이터 노드
	map<string, VaccinationData*>* pMap = pDataNode->getDataMap();

	int splitIdx = ceil((order - 1) / 2.0) + 1;
	int mapIdx = 0;

	//데이터 노드가 스플릿이 되는 경우는, 데이터노드가 찢어져서 왼쪽 데이터노드, 오른쪽 데이터노드 그리고 이들을 자식으로 가지는 인덱스 노드가 생깁니다.
	//실제로 찢어질 순 없으니 기존 데이터노드가 왼쪽 데이터 노드 역할을 하고, 나머지 오른쪽 데이터 노드와 인덱스 노드는 새로 생성해줍니다.
	//아래 반복문은 기존에 찢어질 데이터노드가 가진 데이터를 새로 생긴 우측 데이터 노드에 값을 분배하고, 분배한 값은 지워줍니다.

	BpTreeDataNode* dataNode = new BpTreeDataNode;	//스플릿후 이어질 우측 데이터 노드
	for (auto it = (*pMap).begin(); it != (*pMap).end(); )		//pMap은 맵을 가르키고 있어서 맵 처음부터 끝까지 순환하는 것입니다.
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

	//우측 데이터 노드가 새로 생겼으니, 기존노드(왼쪽 데이터 노드)랑 이어줍니다.
	//서로 next prev 이어주기
	dataNode->setNext(pDataNode->getNext());
	if (pDataNode->getNext() != nullptr)
		pDataNode->getNext()->setPrev(dataNode);

	dataNode->setPrev(pDataNode);
	pDataNode->setNext(dataNode);

	BpTreeIndexNode* indexNode = new BpTreeIndexNode;	//올라갈 인덱스 노드, 노드 올리고 아래 두 data 노드 연결
	indexNode->setMostLeftChild(pDataNode);	// 최좌측 노드
	map<string, VaccinationData*>* dataMap = dataNode->getDataMap();
	indexNode->insertIndexMap(dataMap->begin()->first, dataNode); //자식 노드

	dataNode->setParent(indexNode);
	pDataNode->setParent(indexNode);

	if (pDataNode == root)
		root = indexNode;

	//Print();
	if (exceedIndexNode(indexNode))			//인덱스 노드를 생성했는데, 인덱스 스플릿이 또 일어날 경우
		splitIndexNode(indexNode);

	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	map<string, BpTreeNode*>* pMap = pIndexNode->getIndexMap();

	int mapIdx = 0;

	if (pIndexNode->getParent() == nullptr)
	{
		//pIndexNode 좌측인덱스
		BpTreeIndexNode* parentIndexNode = new BpTreeIndexNode;	//부모 인덱스
		BpTreeIndexNode* rightIndexNode = new BpTreeIndexNode;  //우측 인덱스
		
		for (auto it = (*pMap).begin(); it != (*pMap).end(); )
		{
			if (mapIdx == 0)			// 좌측 인덱스 노드는 그대로 냅둬도 된다. mostLeft와 자식노드가 변경이 필요없다.
				continue;
			else if (mapIdx == 1)
			{
				rightIndexNode->setMostLeftChild(it->second);		//우측노드는 올라간(부모) 노드에 자식은 최좌측노드로 가진다.
				parentIndexNode->insertIndexMap(it->first, rightIndexNode); //부모노드는 중간에 있던 문자열을 인덱스로 받고, 자식노드는 우측노드로 가진다.
			
				parentIndexNode->setMostLeftChild(pIndexNode);				//부모노드의 좌측노드

				pIndexNode->setParent(parentIndexNode);						//부모설정
				rightIndexNode->setParent(parentIndexNode);
			}
			else
			{
				rightIndexNode->insertIndexMap(it->first, it->second);	//우측노드의 자식노드는 이전과 같다.
				it->second->setParent(rightIndexNode);					//자식노드들의 부모설정도 바꿔준다.
			}
		}


	}
	else
	{
		//pIndexNode 좌측인덱스
		BpTreeNode* parentIndexNode = pIndexNode->getParent(); 	//부모 인덱스
		BpTreeIndexNode* rightIndexNode = new BpTreeIndexNode;  //우측 인덱스

		for (auto it = (*pMap).begin(); it != (*pMap).end(); )
		{
			if (mapIdx == 0)			// 좌측 인덱스 노드는 그대로 냅둬도 된다. mostLeft와 자식노드가 변경이 필요없다.
				continue;
			else if (mapIdx == 1)
			{
				rightIndexNode->setMostLeftChild(it->second);		//우측노드는 올라간(부모) 노드에 자식은 최좌측노드로 가진다.
				parentIndexNode->insertIndexMap(it->first, rightIndexNode); //부모노드는 중간에 있던 문자열을 인덱스로 받고, 자식노드는 우측노드로 가진다.
				
				parentIndexNode->setMostLeftChild(pIndexNode);

				pIndexNode->setParent(parentIndexNode);
				rightIndexNode->setParent(parentIndexNode);

				if (exceedIndexNode(parentIndexNode))
					splitIndexNode(parentIndexNode);
			}
			else
			{
				rightIndexNode->insertIndexMap(it->first, it->second);	//우측노드의 자식노드는 이전과 같다.
				it->second->setParent(rightIndexNode);					//자식노드들의 부모설정도 바꿔준다.
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
	else                 //데이터가 없는 경우
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

void BpTree::deleteTree(BpTreeNode* curNode)			//트리 삭제
{
	if (curNode == nullptr)
		return;
	if (curNode->getIsLeap() == true)					//좌측 삭제
	{
		delete curNode;
		return;
	}

	deleteTree(curNode->getMostLeftChild());

	delete curNode;										//본체 삭제 (우측노드 삭제는 소멸자에서 진행)
	root = nullptr;
	return;
}