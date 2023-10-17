#include <iostream>

using namespace std;
int idx = 0;
HashTable::HashTable()
{
    used = 0;
    size = 0;
    hashData = nullptr;
}

HashTable::HashTable(int size)
{
    used = 0;
    this->size = size;
    hashData = new studentRecord[size];
    for (size_t i = 0; i < size; i++)
    {
        hashData[i].studentID = -1;
    }
}

int HashTable::getUsed() const
{
    return used;
}

void HashTable::setSize(int s)
{
    size = s;
    hashData = new studentRecord[size];
    for (size_t i = 0; i < size; i++)
    {
        hashData[i].studentID = -1;
    }
}

int HashTable::getSize() const
{
    return size;
}

void HashTable::insert(const studentRecord& student)
{
    int index = 0;
    bool itemPresent = findIndex(student.studentID, index);
    
    if (!itemPresent) {
        assert(getUsed() < getSize());
        used++;
    }
    hashData[index] = student;
    
}

bool HashTable::find(int key, studentRecord& student)
{
    bool found{ false };
    
    if (findIndex(key, idx))
    {
        student = hashData[idx];
        cout << "Student Found." << endl;
        found = true;

    }
    else {
        cout << "Student not found." << endl;
    }
    return found;
}

bool HashTable::findIndex(int key, int& i)
{
    bool found{ false };
    int count{ 0 };
    i = hash(key);
    
    return hashData[i].studentID == key;
}

int HashTable::hash(int key) const
{
    return key % getSize();
}

void HashTable::display()
{
    for (size_t i = 0; i < getSize(); i++)
    {
        if (hashData[i].studentID != -1 && hashData[i].studentID != -1000) {
            cout << hashData[i].studentID << " : " << hashData[i].name << " -> " << hashData[i].marks_oop345 << endl;
        }

    }
}

void HashTable::deleteRecord(int key)
{
    int index{ 0 };
    ;
    if (findIndex(key, index)) {
         hashData[index].studentID = -1000;
         hashData[index].name.clear();
         hashData[index].marks_oop345 = 0.0f;
        cout << "Student deleted." << endl;
    }
    else {
        cout << "Student is not in table." << endl;
    }
}

HashTable::~HashTable()
{
    delete hashData;
    hashData = nullptr;
}
