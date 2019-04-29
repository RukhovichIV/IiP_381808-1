#pragma once
#include<string>

using namespace std;

class Request//Представляет собой запрос пользователя
{
public:
	string date;//Дата сеанса
	int time_start;//Время в секундах от 00:00 даты проведения сеанса. [0;86400)
	string film_name;//Название фильма
	int hall_number;//Номер зала
	bool vip;//Тип зоны
	int seats_count;//Желаемое количество мест
	Request();//Конструктор по умолчанию
	Request(const Request& request);//Конструктор копирования
	Request(string date, int time_start,
		string film_name,
		bool vip, int seats_count);//Конструктор инициализации
	~Request();//Деструктор
};