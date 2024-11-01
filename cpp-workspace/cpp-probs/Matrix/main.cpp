#include "Matrix.h"
using namespace std;

int main()
{
	Matrix m1, m2;
	cout << "Input : ";
	cin >> m1; cout << m1;
	cout << "Input : ";
	cin >> m2; cout << m2;
    
	cout << "Add" << endl;
	cout << m1 + m2 << endl;
	
    cout << "Multiply" << endl;
	cout << m1 * m2 << endl;
	return 0;
}
