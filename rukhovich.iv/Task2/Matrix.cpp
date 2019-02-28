#include"Matrix.h"
#include<cstring>
#include<cassert>
#include<cmath>

Matrix::Matrix() : Matrix::Matrix(2) {}

Matrix::Matrix(const Matrix& _m, int _new_size)
{
	assert(_new_size >= 1 && _new_size <= 8);
	if (_new_size <= _m.size)//Razmer ne izmenilsya ili umen'shilsya
	{
		size = _new_size;
		if (size == 1)
			size = _m.size;
		mtx = new int*[size];
		for (int i = 0; i < size; ++i)
		{
			mtx[i] = new int[size];
			memcpy(mtx[i], _m.mtx[i], size << 2);
		}
	}
	else//Razmer novoy matritsi bol'she - zapolnyaem ostatok nulyami
	{
		Matrix(new_size);
		for (int i = 0; i < size; ++i)
			memcpy(mtx[i], _m.mtx[i], size << 2);
	}
}

Matrix::Matrix(int _size, int _fill)
{
	assert(_size >= 2 && _size <= 8);
	size = _size;
	mtx = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		mtx[i] = new int[size];
		for (int j = 0; j < size; ++j)
			mtx[i][j] = _fill;
	}
}

Matrix::Matrix(int _size, int** _arr)
{
	size = _size;
	mtx = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		mtx[i] = new int[size];
		for (int j = 0; j < size; ++j)
			mtx[i][j] = _arr[i][j];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < size; ++i)
		delete mtx[i];
	delete mtx;
	size = 1;
}

void Matrix::set_len(int _len)
{
	assert(_len >= 2 && _len <= 8);
	if (_len == size)
		return;
	int** new_mat = new int*[_len];
	if(_len < size)
		for (int i = 0; i < _len; ++i)
		{
			new_mat[i] = new int[_len];
			memcpy(new_mat[i], mtx[i], _len << 2);
		}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			new_mat[i] = new int[_len];
			memcpy(new_mat[i], mtx[i], size << 2);
			memset(new_mat[i]+size, 0, (_len - size) << 2);
		}
		for (int i = size; i < _len; ++i)
		{
			new_mat[i] = new int[_len];
			memset(new_mat[i], 0, _len << 2);
		}
	}
	for (int i = 0; i < size; ++i)
		delete mtx[i];
	delete mtx;
	mtx = new_mat;
	size = _len;
}

int Matrix::get_len()
{
	return size;
}

void Matrix::set(int _i, int _j, int _val)
{
	assert(_i > 0 && _i <= size && _j > 0 && _j <= size);
	mtx[_i - 1][_j - 1] = _val;
}

int Matrix::get(int _i, int _j)
{
	assert(_i > 0 && _i <= size && _j > 0 && _j <= size);
	return mtx[_i - 1][_j - 1];
}

typedef long long i64;

bool Matrix::diagonally_dominance()
{
	bool have_strong_dom = false;
	for (int i = 0; i < size; ++i)
	{
		i64 sum = 0;
		for(int j = 0; j < size; ++j)
			sum += mtx[i][j];
		sum -= mtx[i][i];
		if (abs(sum) > abs(mtx[i][i]))
			return false;
		if (abs(sum) < abs(mtx[i][i]))
			have_strong_dom = false;
	}
	return have_strong_dom;
}

Matrix Matrix::operator+(const Matrix& _m)
{
	assert(_m.size == size);
	Matrix ans = Matrix(size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			ans.mtx[i][j] = mtx[i][j] + _m.mtx[i][j];
	return ans;
}

Matrix& Matrix::operator+=(const Matrix& _m)
{
	assert(_m.size == size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			mtx[i][j] += _m.mtx[i][j];
	return *this;
}

Matrix Matrix::operator-(const Matrix& _m)
{
	assert(_m.size == size);
	Matrix ans = Matrix(size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			ans.mtx[i][j] = mtx[i][j] - _m.mtx[i][j];
	return ans;
}

Matrix& Matrix::operator-=(const Matrix& _m)
{
	assert(_m.size == size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			mtx[i][j] -= _m.mtx[i][j];
	return *this;
}

Matrix& Matrix::operator=(const Matrix& _m)
{
	for (int i = 0; i < size; ++i)
		delete mtx[i];
	delete mtx;
	size = _m.size;
	mtx = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		mtx[i] = new int[size];
		memcpy(mtx[i], _m.mtx[i], size << 2);
	}
	return *this;
}

#define endl '\n'

std::ostream& operator<<(std::ostream& _s, const Matrix& _m)
{
	_s << _m.size << endl;
	for (int i = 0; i < _m.size; ++i)
	{
		for (int j = 0; j < _m.size; ++j)
			_s << _m.mtx[i][j] << ' ';
		_s << endl;
	}
	return _s;
}

std::istream& operator>>(std::istream& _s, Matrix& _m)
{
	_s >> _m.size;
	assert(_m.size >= 2 && _m.size <= 8);
	_m.mtx = new int*[_m.size];
	for (int i = 0; i < _m.size; ++i)
	{
		_m.mtx[i] = new int[_m.size];
		for (int j = 0; j < _m.size; ++j)
			_s >> _m.mtx[i][j];
	}
	return _s;
}