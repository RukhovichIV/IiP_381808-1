#pragma once
#include"Session.h"

using namespace std;

class Cinema//Кинотеатр
{
public:
	Session* sessions;//Массив всех сеансов в этом месяце
	int count;//Количество сеансов в этом месяце
	Cinema();//Конструктор по умолчанию
	Cinema(const Cinema& cinema);//Конструктор копирования
	Cinema(int count, istream& stream);//Конструктор инициализации - ввод из потока
	~Cinema();//Деструктор
};