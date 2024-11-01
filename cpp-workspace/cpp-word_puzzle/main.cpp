//#include <iostream>
//#include <algorithm>
//#include "Word_puzzle.h"
//#include "BookList.h"
//const string book_list = "books.txt";
//const string puzzle_file = "puzzle.txt";
//
////------------------------------------------------------------//
//// ���⼭���� �ʿ��� �ڵ带 �߰��ϼ���.
//// Ŭ������ �߰��ϰų� �Լ��� �����Ӱ� �߰��ϼ���.
//#include <fstream>
//#include <set>
//#include <vector>
//#include <ctime>
//set <string> s;
//set <string> v;
//matrix <string> puzzle_grid(8, 8);
//
//void BookList_Read_Line(const string& bookname)
//{
//	ifstream ifs;
//	ifs.open(bookname, ios::in);
//
//	if (ifs.is_open())
//	{
//		string line;
//		while (getline(ifs, line))  // ifs ���Ͽ��� newline ���� ���پ� �д´�.
//		{
//
//			transform(line.begin(), line.end(), line.begin(), ::tolower);
//
//			//slice_line_To_Token(line);
//			char* str = NULL;
//			char* token = strtok_s((char*)line.c_str(), " \t", &str);
//
//			while (token != NULL)
//			{
//				s.insert(token);
//				token = strtok_s(NULL, " \t", &str);
//			}
//		}
//		ifs.close();
//	}
//}
//void Word_puzzle::read_dic_file(const string& dic_file)
//{
//	puzzle_grid = m_puzzle;
//}
//
//void make_word_in_puzzle(matrix<string> puzzle_grid) {
//
//	for (int a = 0; a < 6; a++) {
//		for (int row = 0; row < puzzle_grid.numrows(); row++) // ���� -> ���� ����
//		{
//			string row_line = "";
//			for (int col = a; col < puzzle_grid.numcols(); col++)
//			{
//				row_line += puzzle_grid[row][col]; //�ѱ��� �� �����ֱ�
//				row_line.erase(find_if(row_line.begin(), row_line.end(), ::isspace), row_line.end());
//				if (s.find(row_line) != s.end() && (row_line.length() >= 3))
//				{
//					v.insert(row_line);
//				}
//			}
//		}
//	}
//	for (int a = 0; a < 6; a++) {
//		for (int row = puzzle_grid.numrows() - 1; row >= 0; row--) // ���� -> ���� ����
//		{
//			string row_line = "";
//			for (int col = puzzle_grid.numcols() - 1 - a; col >= 0; col--)
//			{
//				row_line += puzzle_grid[row][col]; //�ѱ��� �� �����ֱ�
//				row_line.erase(find_if(row_line.begin(), row_line.end(), ::isspace), row_line.end());
//				if (s.find(row_line) != s.end() && (row_line.length() >= 3))
//				{
//					v.insert(row_line);
//				}
//			}
//		}
//	}
//	for (int a = 0; a < 6; a++) {
//		for (int col = 0; col < puzzle_grid.numcols(); col++) // �� -> �Ʒ� ����
//		{
//			string col_line = "";
//			for (int row = a; row < puzzle_grid.numrows(); row++)
//			{
//				col_line += puzzle_grid[row][col];
//				col_line.erase(find_if(col_line.begin(), col_line.end(), ::isspace), col_line.end());
//				if (s.find(col_line) != s.end() && (col_line.length() >= 3))
//				{
//					v.insert(col_line);
//				}
//			}
//		}
//	}
//	for (int a = 0; a < 6; a++) {
//		for (int col = puzzle_grid.numcols() - 1; col >= 0; col--) // �Ʒ� -> �� ����
//		{
//			string col_line = "";
//			for (int row = puzzle_grid.numrows() - 1 - a; row >= 0; row--)
//			{
//				col_line += puzzle_grid[row][col];
//				col_line.erase(find_if(col_line.begin(), col_line.end(), ::isspace), col_line.end());
//				if (s.find(col_line) != s.end() && (col_line.length() >= 3))
//				{
//					v.insert(col_line);
//				}
//			}
//
//		}
//	}
//	for (int a = 0; a < 6; a++) { //�밢�� ���� ������ ������ �Ʒ�
//		string diagonal_line = "";
//		for (int i = a; i < 8; i++) {
//			diagonal_line += puzzle_grid[i][i];
//			diagonal_line.erase(find_if(diagonal_line.begin(), diagonal_line.end(), ::isspace), diagonal_line.end());
//			if (s.find(diagonal_line) != s.end() && (diagonal_line.length() >= 3))
//			{
//				v.insert(diagonal_line);
//			}
//		}
//	}
//	for (int a = 7; a >= 3; a--) { //�밢�� ������ �Ʒ����� ���� ��
//		string diagonal_line = "";
//		for (int i = a; i >= 0; i--) {
//			diagonal_line += puzzle_grid[i][i];
//			diagonal_line.erase(find_if(diagonal_line.begin(), diagonal_line.end(), ::isspace), diagonal_line.end());
//			if (s.find(diagonal_line) != s.end() && (diagonal_line.length() >= 3))
//			{
//				v.insert(diagonal_line);
//			}
//		}
//	}
//	for (int a = 0; a < 6; a++) { //�밢�� ���� �ؿ��� ������ ��
//		string diagonal_line = "";
//		for (int i = a; i < 8; i++) {
//			int j = 7 - i;
//			diagonal_line += puzzle_grid[j][i];
//			diagonal_line.erase(find_if(diagonal_line.begin(), diagonal_line.end(), ::isspace), diagonal_line.end());
//			if (s.find(diagonal_line) != s.end() && (diagonal_line.length() >= 3))
//			{
//				v.insert(diagonal_line);
//			}
//		}
//	}
//	for (int a = 0; a < 6; a++) { // �밢�� ������ ������ ���� ��
//		string diagonal_line = "";
//		for (int i = a; i < 8; i++) {
//			int j = 7 - i;
//			diagonal_line += puzzle_grid[i][j];
//			diagonal_line.erase(find_if(diagonal_line.begin(), diagonal_line.end(), ::isspace), diagonal_line.end());
//			if (s.find(diagonal_line) != s.end() && (diagonal_line.length() >= 3))
//			{
//				v.insert(diagonal_line);
//			}
//		}
//	}
//}
//
//
//vector<string> your_answer1()
//{
//	vector <string> end;
//	for (auto a : v) {
//		end.push_back(a);
//	}
//	return end;
//}
//
//// ������� �ʿ��� �ڵ带 �߰��ϼ���
////------------------------------------------------------------//
//
//
//
//void print_result(vector<string> & words)
//{
//	// �ҹ��ڷ� ��ȯ�Ѵ�.
//	for (auto& word : words)
//		std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return tolower(c); });
//
//	// �����Ѵ�.
//	sort(words.begin(), words.end());
//
//	// ����Ѵ�.
//	for (auto& word : words)
//		cout << word << endl;
//
//}
//
//int main()
//{
//	clock_t start, finish;
//	start = clock();
//
//	Word_puzzle puzzle(puzzle_file, 8, 8);
//	BookList booklist(book_list);
//
//	cout << "\n\n������ ����Ʈ�Ѵ�. (8 X 8 ����)" << endl << endl;
//	puzzle.print_puzzle();
//
//	cout << "\n\nå����� ����Ʈ�Ѵ�." << endl << endl;
//	booklist.print_booklist();
//
//	//------------------------------------------------------------//
//	// ���⼭���� �ʿ��� �ڵ带 �߰��ϼ���.
//
//	for (auto a : booklist.list_books()) {
//		BookList_Read_Line(a); //å �̸��� �ϳ� �� �־ �ϳ��� å�� �ִ� �ܾ���� set �� ���� �ϳ��� �־�α�. (�ߺ�����)
//	}
//
//	puzzle.read_dic_file(puzzle_file);
//	make_word_in_puzzle(puzzle_grid);
//
//	vector<string> words = your_answer1();
//
//	// ������� �ʿ��� �ڵ带 �߰��ϼ���
//	//------------------------------------------------------------//
//
//	cout << "\n\n�������� ������ ����մϴ�. " << endl << endl;
//
//	print_result(words);
//
//
//	finish = clock();
//	cout << "\n\n����ð���" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
//
//	return 0;
//}
//

#include <iostream>

int solve(unsigned long long S, int L) {
    int sum = 0, len = 0, max = 0;
    
    int k = 1;
    while (sum < S/2) {
        sum += k;
        max = k;
        k++;
        len++;
    }
    
    while (--k != L) {
        sum += k;
        len++;
    }
    
    while (sum < S) {
        sum += max;
        len++;
    }
    
    return len;
}

int main(void) {
    unsigned long long S;
    int L;
    
    scanf("%lld %d", &S, &L);
    
    int result = solve(S, L);
    printf("%d\n", result);
}
