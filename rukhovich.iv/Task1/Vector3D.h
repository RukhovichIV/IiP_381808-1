#pragma once
#include<iostream>

class Vector3D 
{
public:
	Vector3D();//konstruktor po umolchaniyu
	Vector3D(const Vector3D&);//konstruktor kopirovaniya
	Vector3D(int, int = 0, int = 0);//konstruktor initsializatsii
	Vector3D(double, double = 0, double = 0);//konstruktor initsializatsii
	~Vector3D();//destruktor
	Vector3D& operator=(const Vector3D&);//prisvaivanie
	Vector3D operator+(const Vector3D&);//slozhenie
	Vector3D& operator+=(const Vector3D&);//pribavlenie
	Vector3D operator-(const Vector3D&);//vichitanie
	Vector3D& operator-=(const Vector3D&);//vichitanie
	Vector3D Mult(const Vector3D&);//vectornoe proizvedenie
	double operator*(const Vector3D&);//scalarnoe proizvedenie
	Vector3D operator*(const double&);//umnozhenie na chislo
	Vector3D& operator*=(const double&);//domnozhenie na cjislo
	Vector3D operator/(const double&);//delenie na chislo
	Vector3D& operator/=(const double&);//dodelenie na cjislo
	const bool operator>(const Vector3D&);//sravnenie
	const bool operator<(const Vector3D&);//sravnenie
	const bool operator==(const Vector3D&);//sravnenie
	const bool operator!=(const Vector3D&);//sravnenie
	friend std::ostream& operator<<(std::ostream&, const Vector3D&);//vivod v potok
	friend std::istream& operator>>(std::istream&, Vector3D&);//vvod iz potoka
private:
	double x, y, z;//komponenti vectora
	double length;//dlina vectora
	static constexpr double eps = 1e-10;//constanta dlya proverki vectorov na ravenstvo
	void CalculateLength();//funktsiya dlya nahozhdeniya dlini vectora
};