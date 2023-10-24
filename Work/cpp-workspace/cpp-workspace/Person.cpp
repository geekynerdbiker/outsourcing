#include "Person.h"

ostream& operator<<(ostream& fout, const Person& p) {
    fout << "name : " << left << setw(10) << right << p.get_name()<< ", "
		<< "date_of_birth : " << p.get_DoB();

	return fout;
}
