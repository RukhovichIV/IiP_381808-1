#include<iostream>
#include<cmath>

using namespace std;

#define ret return
#define PI 3.14159265358979323846
#define eps 1e-8

//--------------TODO  class Angle------------------
/*class Angle
{
private:
	double a;
private:
	Angle();
	Angle(const Angle&);
	template<class T> Angle(T);
	~Angle();
	double Ang();
	void Ang(double);
	double Cos();
	double Sin();
	double Tg();
};
double Angle::Ang()
{
	ret this->a;
}
void Angle::Ang(double a)
{
	this->a = a;
}*/
//-----------------------------------------------

class Triangle
{
private:
	double a, b, c;
	bool calculated;
	bool norm;
	bool ex;
	string angleT;
	double per;
	double sq;
public:
	Triangle();
	Triangle(const Triangle&);
	template<class T> Triangle(T, T, T);
	~Triangle();

	void Calculate();
	void Normalize();
	bool exists();
	string angleType();
	double perimeter();
	double square();
};
Triangle::Triangle()
{
	a = b = c = 0;
	calculated = false;
}
Triangle::Triangle(const Triangle& t)
{
	a = t.a;
	b = t.b;
	c = t.c;
	calculated = t.calculated;
}
template<class T> Triangle::Triangle(T a, T b, T c)
{
	this->a = (double)a;
	this->b = (double)b;
	this->c = (double)c;
	calculated = false;
}
Triangle::~Triangle()
{
	a = b = c = 0;
	calculated = false;
}

void Triangle::Normalize()
{
	if (a < b)
		swap(a, b);
	if (a < c)
		swap(a, c);
	if (b < c)
		swap(b, c);
	norm = true;
}
bool Triangle::exists()
{
	if (calculated)
		ret ex;
	if (norm)
	{
		if (b + c > a)
			ret true;
		ret false;
	}
	Triangle t = Triangle(*this);
	t.Normalize();
	if (t.b + t.c > t.a)
		ret true;
	ret false;
}
string Triangle::angleType()
{
	if (calculated)
		ret angleT;
	if (!exists())
		ret "error";
	double cosa = (c*c + b*b - a*a) / 2 / b / c;
	double alpha = acos(cosa);
	double beta = asin(b / a*sqrt(1 - cosa*cosa));
	double gamma = PI - alpha - beta;
	double maxang = alpha;
	if (beta > maxang)
		maxang = beta;
	if (gamma > maxang)
		maxang = gamma;
	if (maxang > PI / 2 + eps)
		ret "obtuse";
	if (maxang > PI / 2 - eps)
		ret "rectangular";
	ret "acute";
}
double Triangle::perimeter()
{
	if (calculated)
		ret per;
	ret a + b + c;
}
double Triangle::square()
{
	if (calculated)
		ret sq;
	double semiper = perimeter() / 2;
	ret sqrt(semiper*(semiper - a)*(semiper - b)*(semiper - c));
}
void Triangle::Calculate()
{
	ex = exists();
	angleT = angleType();
	per = perimeter();
	sq = square();
	calculated = true;
}

int main()
{

	return 0;
}