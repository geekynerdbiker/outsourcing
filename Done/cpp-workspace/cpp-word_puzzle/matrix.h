#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
using namespace std;

template <typename Object>
class matrix
{
public:

	matrix(int rows, int cols) : array(rows) //행과 열을 인수로 받아 지정된 크기로 만들기
	{
		for (auto & thisRow : array)
			thisRow.resize(cols);
	}

	matrix(initializer_list<vector<Object>> lst) : array(lst.size()) //초기화 인수 받아서 목록에서 행렬을 만들기
	{
		int i = 0;
		for (auto & v : lst)
			array[i++] = std::move(v);
	}

	matrix(const vector<vector<Object>> & v) : array{ v }  //복사 생성자
	{ }
	matrix(vector<vector<Object>> && v) : array{ std::move(v) } //이동 생성자
	{ }

	const vector<Object> & operator[](int row) const
	{
		return array[row];
	}
	vector<Object> & operator[](int row)
	{
		return array[row];
	}

	int numrows() const
	{
		return array.size();
	}
	int numcols() const
	{
		return numrows() ? array[0].size() : 0;
	}
private:
	vector<vector<Object>> array;
};

#endif



