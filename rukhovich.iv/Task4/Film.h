#pragma once
#include<string>

using namespace std;

class Film
{
public:
	string name;//Название фильма
	string director;//Режиссер
	string scriptwriter;//Сценарист
	string composer;//Композитор
	string date;//Дата выхода
	int year;//Год выхода (вычисляется из даты)
	long long gross;//Суммарная прибыль
	Film(const string& name = "<unknown>",//Конструктор по умолчанию и инициализации
		const string& director = "<unknown>",
		const string& scriptwriter = "<unknown>",
		const string& composer = "<unknown>",
		const string& date = "01.01.1800",
		const int year = 1800,
		const long long gross = 0);
	Film(const Film& film);//Конструктор копирования
	~Film();//Деструктор
	bool operator<(const Film& film) const;//Оператор сравнения (по названию и году выхода)
	bool operator>(const Film& film) const;//Оператор сравнения (по названию и году выхода)
	bool operator==(const Film& film) const;//Оператор сравнения (по названию и году выхода)
	bool operator!=(const Film& film) const;//Оператор сравнения (по названию и году выхода)
	Film& operator=(const Film& film);//Оператор присваивания
};