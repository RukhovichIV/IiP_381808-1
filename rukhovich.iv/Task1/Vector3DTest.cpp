#include<iostream>
#include"Vector3D.h"

using namespace std;

int main()
{
	Vector3D v1(3, 4, 12), v2(17.0, 47.1), v3(v2);
	cout << v1 << '\n' << v2 << '\n' << v3 << '\n';
	v1 /= 2;
	cout << v1 << '\n';
	Vector3D sum = v1 + v2;
	if (sum > 15)
		cout << sum << '\n';
	else
		cout << "15\n";
	double d = v1*v2;
	Vector3D mult = v1.Mult(v2) / 5 - v3;
	cout << d << '\n' << mult;
	return 0;
}