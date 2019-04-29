#include"TicketOffice.h"
#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите текущую дату и время в формате дд.мм.гггг чч:мм: ";
	char tmp;
	string date;
	int hours, minutes;
	cin >> date >> hours >> tmp >> minutes;
	cout << "Введите имя файла с расписанием сеансов: ";
	string path;
	cin >> path;
	fstream fin(path, ios_base::in);
	int count;
	fin >> count;
	string tmp_s;
	getline(fin, tmp_s);//Переход на новую строку
	TicketOffice office = TicketOffice(date, (60*hours+minutes)*60, fin, count);
	while (1)
	{
		system("cls");
		cout << "Добро пожаловать в наш кинотеатр\n";
		cout << "Список возможных действий:\n";
		cout << "</reserve>\t\t - забронировать места на фильм\n";
		cout << "</pay>\t\t - выкупить забронированные места\n";
		cout << "</cancel>\t\t - отменить резерв мест\n";
		cout << "</exit>\t\t - выйти из программы";
		string answer;
		cin >> answer;
		if (answer == "/exit")
			return 0;

		cout << "Введите название фильма ";
		string name;
		getline(cin, name);
		cout << "Введите дату и время начала фильма в формате дд.мм.гггг чч:мм ";
		cin >> date >> hours >> tmp >> minutes;
		return 0;
		if (office.current_time / 60 - (60 * hours + minutes) > 10)
		{
			cout << "Прошло больше 10 минут с момента начала сеанса. Продажа билетов окончена";
			continue;
		}
		cout << "Введите <vip>, если требуются vip-места, иначе введите <obvious> ";
		string vip;
		cin >> vip;
		cout << "Введите количество мест: ";
		int seats;
		cin >> seats;
		Request r = Request(date, (60 * hours + minutes) * 60, name, vip == "vip", seats);
		int ans = office.Check(r);
		if (ans == 1)
		{
			cout << "В это время нет такого фильма";
			continue;
		}
		else if (ans == 2)
		{
			cout << "В зале нет такого количества мест";
			continue;
		}

		if (answer == "/pay")
		{		
			double cost = office.Calculate(r);
			cout << "Суммарная стоимость: " << cost << '\n';
			/*Как-бы происходит оплата*/
			cout << "Вот ваши билеты:\n";
			office.Pay(r, cout);//Билеты будут выведены в поток
		}
		else if (answer == "/reserve")
		{
			bool result = office.Reserve(r);
			if (result)
				cout << "Места успешно забронированы. Не забудьте выкупить их перед сеансом\n";
			else
				cout << "Не удалось забронировать места (нет такого количества мест)";
		}
		else if(answer == "/cancel")
		{
			office.Cancel(r);
			cout << "Резерв успешно отменён.";
		}
	}
	return 0;
}