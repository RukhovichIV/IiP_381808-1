#pragma once
#include<string>

using namespace std;

class Session//Сеанс показа фильма
{
public:
	string date;//Дата проведения
	int time_start;//Время в секундах от 00:00 даты проведения сеанса. [0;86400)
	string film_name;//Название фильма
	int hall_number;//Номер зала
	int cost;//Базовая стоимость билета
	int row_count;//Количество рядов в зале
	int seats_in_a_row;//Количество сидений на одном ряду
	char* seats;//Состояние мест в зале (0 - свободно, 1 - зарезервировано, 2 - выкуплено)
	//Будем считать, что в каждом зале первые 2 ряда - VIP-места. (в задании ничего не сказано о количестве VIP-мест)
	Session();//Конструктор по умолчанию
	Session(const Session& session);//Конструктор копирования
	Session(const string& date, const int& time_start,
		const string& film_name, const int& hall_number,
		const int& cost, const int& row_count, const int& seats_in_a_row);//Конструктор инициализации
	~Session();//Деструктор
	friend istream& operator>>(istream& stream, Session& session);//Ввод сеанса
};