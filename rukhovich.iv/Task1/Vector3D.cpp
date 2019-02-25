#include"Vector3D.h"
#include<math.h>
#include<iostream>

Vector3D::Vector3D()
{
	x = y = z = length = 0;
}

Vector3D::Vector3D(int a, int b, int c)
{
	x = int(a);
	y = int(b);
	z = int(c);
	CalculateLength();
}

Vector3D::Vector3D(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
	CalculateLength();
}

Vector3D::Vector3D(const Vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	length = v.length;
}

Vector3D::~Vector3D()
{
	x = y = z = length = 0;
}

void Vector3D::CalculateLength()
{
	length = sqrt(x*x + y*y + z*z);
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	length = v.length;
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v)
{
	Vector3D res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	res.CalculateLength();
	return res;
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	CalculateLength();
	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
	Vector3D res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	res.CalculateLength();
	return res;
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	CalculateLength();
	return *this;
}

Vector3D Vector3D::Mult(const Vector3D& v)//vector multiplication
{
	Vector3D res;
	res.x = y*v.z - z*v.y;
	res.y = x*v.z - z*v.x;
	res.z = x*v.y - y*v.x;
	res.CalculateLength();
	return res;
}

double Vector3D::operator*(const Vector3D& v)//scalar multiplication
{
	return x*v.x + y*v.y + z*v.z;
}

Vector3D Vector3D::operator*(const double& d)
{
	Vector3D res(*this);
	res.x *= d;
	res.y *= d;
	res.z *= d;
	res.length *= d;
	return res;
}

Vector3D& Vector3D::operator*=(const double& d)
{
	x *= d;
	y *= d;
	z *= d;
	length /= d;
	return *this;
}

Vector3D Vector3D::operator/(const double& d)
{
	return *this*(1 / d);
}

Vector3D& Vector3D::operator/=(const double& d)
{
	return *this *= (1 / d);
}

const bool Vector3D::operator>(const Vector3D& v)
{
	return length - eps > v.length;
}

const bool Vector3D::operator<(const Vector3D& v)
{
	return length + eps < v.length;
}

const bool Vector3D::operator==(const Vector3D& v)
{
	return length + eps > v.length && length - eps < v.length;
}

const bool Vector3D::operator!=(const Vector3D& v)
{
	return !(length == v.length);
}

std::ostream& operator<<(std::ostream& s, const Vector3D& v)
{
	s << "X: " << v.x << "\nY: " << v.y << "\nZ: " << v.z << "\nLength: " << v.length << "\n";
	return s;
}

std::istream& operator>>(std::istream& s, Vector3D& v)
{
	s >> v.x >> v.y >> v.z;
	v.CalculateLength();
	return s;
}