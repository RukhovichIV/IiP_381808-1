#pragma once
#include<iostream>
class Matrix
{
private:
	int size = 1;//Razmer matritsi
	int** mtx;//Matritsa
public:
	Matrix();//Konstruktor po umolchaniyu
	Matrix(const Matrix&, int = 1);//Konstruktor kopirovaniya s vozmozhnost'yu izmeneniya razmera matritsi
	Matrix(int, int = 0);//Konstruktor initsializacii s zapolneniem nachal'nim znacheniem
	Matrix(int, int**);//Konstruktor preobrazovaniya massiva v matritsu
	~Matrix();//Destruktor
	void set_len(int);//Zadanie razmera. Pri umen'shenii otbrasivayutsa elementi iz pravogo nizhnego ugla
	//Pri uvelichenii novie elementi stanovyatsa nulyami
	int get_len();//Poluchenie razmera matritsi
	void set(int, int, int);//Zadanie elementa stroki i stolbtsa j
	int get(int, int);//Poluchenie elementa po indexu
	bool diagonally_dominance();//Proverka diagonal'nogo preobladaniya
	Matrix operator+(const Matrix&);//Slozhenie matrits
	Matrix& operator+=(const Matrix&);//Slozhenie matrits
	Matrix operator-(const Matrix&);//Vichitanie matrits
	Matrix& operator-=(const Matrix&);//Vichitanie matrits
	Matrix& operator=(const Matrix&);//Prisvaivanie matrits
	friend std::ostream& operator<<(std::ostream&, const Matrix&);//Vivod matritsi v potok
	friend std::istream& operator>>(std::istream&, Matrix&);//Vvod matritsi iz potoka
};