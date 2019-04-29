#pragma once
#include"Cinema.h"
#include"Request.h"

using namespace std;

class TicketOffice//Билетная касса
{
private:
	Cinema cinema;//Кинотеатр
	void Show_ticket(ostream& stream, const Request& request, int row_number, int seat_number);//Служебная функция, выводящаа в поток билет
public:
	string date_today;//Сегодняшняя дата
	int current_time;//Текущее время
	TicketOffice();//Конструктор по умолчанию
	TicketOffice(const TicketOffice& office);//Конструктор копирования
	TicketOffice(const string& date_today, const int& current_time,
		istream& stream, const int& count);//Конструктор инициализации
	~TicketOffice();//Деструктор
	void Pay(const Request& request, ostream& stream);//Оплата и вывод билетов в поток
	int Check(Request& request) const;//Проверка наличия свободных мест
	bool Reserve(Request& request);//Резервирование мест. В случае успеха возварщает true
	double Calculate(const Request& request) const;//Расчет стоимости билетов
	void Cancel(const Request& request);//Отмена резерва. В случае успеха возварщает true
	void Set_date_and_time(const string& date_today, const int& current_time);//Задать текущую дату и время
};