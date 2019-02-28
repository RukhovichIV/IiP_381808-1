#include"Matrix.h"
#include<fstream>

using namespace std;

int main()
{
	Matrix m1, m2;
	ifstream fin("D:\\Desktop\\in.txt");//Soderzhimoe:
	/* 3
	1 2 3
	4 5 6
	7 8 9
	6
	2 5 1 2 5 1 4 1 3
	7 8 4 4 1 3 7 8 4
	2 5 1 2 5 1 4 1 3
	7 8 4 4 1 3 7 8 4
	2 5 1 2 5 1 4 1 3
	7 8 4 4 1 3 7 8 4*/
	ofstream fout("D:\\Desktop\\out.txt");
	fin >> m1 >> m2;
	m1.set_len(5);
	m2.set_len(5);
	Matrix m3(m2);
	m1.set(3, 4, -1);
	fout << m1 + m3;
}