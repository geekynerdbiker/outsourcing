#include "Manager.h"
#include <fstream>
#include <string>
#include <vector>
#include<sstream>

using namespace std;

Manager::Manager(int bpOrder) : bp(nullptr), avl(nullptr){
	argVec.reserve(5);
}

Manager::~Manager() {
	if( bp )
		delete bp;
	if (avl)
		delete avl;
}

void Manager::run(const char* command_txt) {
	ifstream in(command_txt);
	string cmd, argStr;
	

	while (in>> cmd)  // ��ɾ� �Է�, ���� ù �ܾ�
	{
		getline(in, argStr, '\n'); // ��ɾ� ���� �ܾ�
		argVec.clear();

		if (cmd == "LOAD")
			LOAD();
		else if (cmd == "VLOAD")
		{
			if (avl == nullptr)
			{
				printErrorCode(200);
				continue;
			}
			else
			{
				VLOAD();
			}
		}
		else if (cmd == "ADD")
		{
			istringstream ss(argStr);
			string word = "";
			
			while (getline(ss, word, ' ')) 
				argVec.emplace_back(word);		
			argVec.erase(argVec.begin());
			ADD();
		}
		else if (cmd == "SEARCH_BP")
		{
			istringstream ss(argStr);
			string word = "";

			while (getline(ss, word, ' '))
				argVec.emplace_back(word);
			argVec.erase(argVec.begin());

			if( argVec.size () == 1)
				SEARCH_BP(argVec[0]);
			else 
				SEARCH_BP(argVec[0], argVec[1]);
		}
		else if (cmd == "SEARCH_AVL")
		{
			istringstream ss(argStr);
			string word = "";

			while (getline(ss, word, ' '))
				argVec.emplace_back(word);
			argVec.erase(argVec.begin());

			if (argVec.size() == 1)
				SEARCH_AVL(argVec[0]);
			else
				printErrorCode(500);
		}
		else if (cmd == "VPRINT")
		{
			istringstream ss(argStr);
			string word = "";

			while (getline(ss, word, ' '))
				argVec.emplace_back(word);

			if (argVec.empty())
			{
				printErrorCode(600);
				continue;
			}
			else
				argVec.erase(argVec.begin());

			if (argVec.size() == 1)
				VPRINT(argVec[0]);
			else
				printErrorCode(600);
		}
		else if (cmd == "PRINT_BP")
		{
			bp->Print();
		}
		else if (cmd == "EXIT")
		{
			//cout << "EXIT" << endl;
			if (bp)
				delete bp;
			if (avl)
				delete avl;
		}
		else
			printErrorCode(800);

	}

	return;
}

bool Manager::LOAD() {
	ifstream in("input_data.txt");
	string name = "", vaccin = "", times = "", age = "", loc = "";

	ofstream out("log.txt");

	if (!in) //����1 ���� ���� ��
	{
		printErrorCode(100);
		return false;
	}
	else if (bp != nullptr)//����3 Ʈ���� �����ϴ� ���
	{
		printErrorCode(100);
		return false;
	}
	else
	{	//������ �ҷ�����
		bp = new BpTree;
		avl = new AVLTree;
		int testIdx = 0;
		while (in >> name >> vaccin >> times >> age >> loc)
		{
			VaccinationData* data = new VaccinationData;
			data->SetUserName(name);
			data->SetVaccineName(vaccin);
			data->SetTimes(stoi(times));
			data->SetAge(stoi(age));
			data->SetLocationName(loc);

			bp->Insert(data);
			//cout << testIdx++ << " " << name;
			//bp->Print();
		}

		
		if (loc.empty()) //����2 ���Ͼȿ� �����Ͱ� ���� ���
		{
			printErrorCode(100);
			return false;
		}
		else
		{
			out << "========LOAD========" << endl;
			out << "Success" << endl;
			out << "=====================" << endl << endl;
		}
	}

	return true;

}

bool Manager::VLOAD() {
	Print_vector.clear();
	avl->GetVector(Print_vector);

	ofstream out("log.txt", ios::app);
	out << "========VLOAD========" << endl;
	out << "Success" << endl;
	out << "=====================" << endl << endl;
	return false;
}

bool Manager::ADD() {

	ofstream out("log.txt", ios::app);

	//argVec ex) Elsa Janssen 49 Busan
	if (argVec.size() != 4)
	{
		printErrorCode(300);

		return false;
	}
	BpTreeNode* findNode = bp->searchDataNode(argVec[0]);
	if( findNode  == nullptr ) //argVec[0] �̸�
	{
		VaccinationData* data = new VaccinationData;
		data->SetUserName(argVec[0]);
		data->SetVaccineName(argVec[1]);
		data->SetTimes(1);											//ADD�� ���� ����� ������ �ϰ� ���°��̱� ������ 1�� �������� �־���
		data->SetAge(stoi(argVec[2]));
		data->SetLocationName(argVec[3]);

		bp->Insert(data);

		if (argVec[1] == "Janssen")								//�Ἶ�� ��� ������ �ٷ� �Ϸ�ϱ� avl��
			avl->Insert(data);
		out << "======== ADD =========" << endl;
		out << argVec[0] << " " << argVec[1] << " " << argVec[2] << " " << argVec[3] << endl;
		out << "=====================" << endl << endl;
	}
	else
	{
		map<string, VaccinationData*>* map = findNode->getDataMap();
		VaccinationData* targetData = (*map)[argVec[0]];
		if (targetData->GetVaccineName() == "Janssen")
		{
			if (targetData->GetTimes() == 1)	//�Ἶ �����Ϸ��� ���
			{
				printErrorCode(300);
				return false;
			}
			else
			{
				targetData->SetTimesInc();
				if (targetData->GetTimes() == 1)	//�Ϸᰡ �Ǿ��� ���, AVL
					avl->Insert(targetData);

				out << "======== ADD =========" << endl;
				out << argVec[0] << " " << argVec[1] << " " << argVec[2] << " " << argVec[3] << endl;
				out << "=====================" << endl << endl;
			}

		}
		else
		{
			if (targetData->GetTimes() == 2)     //�� �� ��� ���� �Ϸ��� ���
			{
				printErrorCode(300);

				return false;
			}
			else
			{
				targetData->SetTimesInc();
				if (targetData->GetTimes() == 2)	//�Ϸᰡ �Ǿ��� ���, AVL
					avl->Insert(targetData);

				out << "======== ADD =========" << endl;
				out << argVec[0] << " " << argVec[1] << " " << argVec[2] << " " << argVec[3] << endl;
				out << "=====================" << endl << endl;
			}
		}
	}
	return false;
}

bool Manager::SEARCH_BP(string name) {		//���� 1��
	ofstream out("log.txt", ios::app);
	BpTreeNode* findNode = bp->searchDataNode(name);

	if (bp == nullptr)			// ��Ʈ���� ���� ���
	{
		printErrorCode(400);

		return false;
	}
	else if (findNode == nullptr)		// �����Ͱ� ���� ���
	{
		printErrorCode(400);

		return false;
	}

	map<string, VaccinationData*>* map = findNode->getDataMap();
	VaccinationData* targetData = (*map)[name];

	out << "======SEARCH_BP=======" << endl;
	out << targetData->GetUserName() << " " << targetData->GetVaccineName() << " " << targetData->GetTimes() << " " << targetData->GetAge() << " " << targetData->GetLocationName() << endl;
	out << "======================" << endl << endl;
	return true;
}

bool Manager::SEARCH_BP(string start, string end) {		//���� 2�� + ����
	
	if (bp == nullptr)			// ��Ʈ���� ���� ���
	{
		printErrorCode(400);

		return false;
	}
	else if (argVec.size() != 2)
	{
		printErrorCode(400);

		return false;
	}
	bp->SearchRange(start, end);

	return false;

}

bool Manager::SEARCH_AVL(string name) {								//�ִ°� ������ ���µ� �Ʒ��� ����
	VaccinationData* targetData = avl->Search(name);
	
	if (targetData == nullptr)
	{
		printErrorCode(400);
	}
	else
	{
		ofstream out("log.txt", ios::app);
		out << "======SEARCH_AVL=======" << endl;
		out << targetData->GetUserName() << " " << targetData->GetVaccineName() << " " << targetData->GetTimes() << " " << targetData->GetAge() << " " << targetData->GetLocationName() << endl;
		out << "======================" << endl << endl;
	}

	return false;

}

string toLower(string s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
	return s;
}

bool Compare(VaccinationData* vac1, VaccinationData* vac2) {		
	
	if (vac1->GetVaccineName() == vac2->GetVaccineName())
	{
		if (vac1->GetAge() == vac2->GetAge())
		{
			string aNameStr = toLower(vac1->GetUserName());
			string bNameStr = toLower(vac2->GetUserName());

			return aNameStr < bNameStr;
		}
		else
			return vac1->GetAge() < vac2->GetAge();
	}
	else
		return vac1->GetVaccineName() < vac2->GetVaccineName();
}

bool CompareB(VaccinationData* vac1, VaccinationData* vac2) {

	if (vac1->GetLocationName() == vac2->GetLocationName())
	{
		if (vac1->GetAge() == vac2->GetAge())
		{
			string aNameStr = toLower(vac1->GetUserName());
			string bNameStr = toLower(vac2->GetUserName());

			return aNameStr < bNameStr;
		}
		else
			return vac1->GetAge() > vac2->GetAge();
	}
	else
		return vac1->GetVaccineName() < vac2->GetVaccineName();
}


bool Manager::VPRINT(string type_) {

	if (avl == nullptr)	//Ʈ���� ����� ���
	{
		printErrorCode(600);

		return false;
	}
	
	ofstream out("log.txt", ios::app);
	if (type_ == "A")
	{
		sort(Print_vector.begin(), Print_vector.end(), Compare);
		out << "======VPRINT A=======" << endl;
	}
	else if (type_ == "B")
	{
		sort(Print_vector.begin(), Print_vector.end(), CompareB);
		out << "======VPRINT B=======" << endl;
	}
	else // �̻��� ��ɾ��� ���
	{
		printErrorCode(600);
		return false;
	}

	for( auto& el : Print_vector)
		out << el->GetUserName() << " " << el->GetVaccineName() << " " << el->GetTimes() << " " << el->GetAge() << " " << el->GetLocationName() << endl;
	out << "======================" << endl << endl;

	return true;
}

void Manager::printErrorCode(int n) {
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	fout << "========== ERROR ==========" <<endl;
	fout << n << endl;
	fout << "===========================" << endl << endl;
	fout.close();
}

