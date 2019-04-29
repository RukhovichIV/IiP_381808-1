#include"TicketOffice.h"

TicketOffice::TicketOffice()
{
	cinema = Cinema();
	date_today = "01.01.1900";
	current_time = 0;
}

TicketOffice::TicketOffice(const TicketOffice& _office)
{
	date_today = _office.date_today;
	current_time = _office.current_time;
	cinema = Cinema(_office.cinema);
}

TicketOffice::TicketOffice(const string& _date_today, const int& _current_time,
	istream& _stream, const int& _count)
{
	date_today = _date_today;
	current_time = _current_time;
	cinema = Cinema(_count, _stream);
}

TicketOffice::~TicketOffice()
{
	cinema.~Cinema();
	date_today = "01.01.1900";
	current_time = 0;
}

void TicketOffice::Show_ticket(ostream& _stream, const Request& _request, int _row_number, int _seat_number)
{
	_stream << "Билет на фильм " << _request.film_name << '\n';
	string time = "";//Время в формате чч:мм
	if (_request.time_start / 60 / 60 < 10)
		time += "0";
	time += to_string(_request.time_start / 60 / 60);
	if (_request.time_start / 60 < 10)
		time += "0";
	time += to_string(_request.time_start / 60);
	_stream << "Дата: " << _request.date << ' ' << time << '\n';
	if (_request.vip)
		_stream << "VIP-место\n";
	_stream << "Зал №" << _request.hall_number << ". Ряд: " << _row_number << " Место: " << _seat_number << '\n';
	_stream << "Стоимость билета: " << Calculate(_request) / _request.seats_count << "\n\n";
}

void TicketOffice::Pay(const Request& _request, ostream& _stream)
{
	int i = 0;
	while (i < cinema.count && (cinema.sessions[i].date != _request.date || cinema.sessions[i].film_name != _request.film_name || cinema.sessions[i].time_start != _request.time_start))
		++i;//Находим нужную сессию
	int cnt = _request.seats_count;
	if (_request.vip)
	{
		int rows = 2;
		if (cinema.sessions[i].row_count < 2)
			rows = cinema.sessions[i].row_count;
		for (int j = 0; j < rows * cinema.sessions[i].seats_in_a_row && cnt > 0; ++j)
			if (cinema.sessions[i].seats[j] == 1)
			{
				cinema.sessions[i].seats[j] = 2;//Оплата места
				Show_ticket(_stream, _request, j / cinema.sessions[i].seats_in_a_row + 1, j % cinema.sessions[i].seats_in_a_row + 1);//Вывод билета в поток
				--cnt;
			}
	}
	else
	{
		for (int j = 2 * cinema.sessions[i].seats_in_a_row; j < cinema.sessions[i].row_count*cinema.sessions[i].seats_in_a_row && cnt > 0; ++j)
			if (cinema.sessions[i].seats[j] == 1)
			{
				cinema.sessions[i].seats[j] = 2;//Оплата места
				Show_ticket(_stream, _request, j / cinema.sessions[i].seats_in_a_row + 1, j % cinema.sessions[i].seats_in_a_row + 1);//Вывод билета в поток
				--cnt;
			}
	}
}

int TicketOffice::Check(Request& _request) const
{
	int i = 0;
	while (i < cinema.count && (cinema.sessions[i].date != _request.date || cinema.sessions[i].film_name != _request.film_name || cinema.sessions[i].time_start != _request.time_start))
		++i;//Поиск сессии по запросу
	if (i == cinema.count)
		return 1;//Такой сессии нет
	//Будем считать, что в каждом зале первые 2 ряда - VIP-места. (в задании ничего не сказано о количестве VIP-мест)
	int cnt = 0;
	if (_request.vip)
	{
		int rows = 2;
		if (cinema.sessions[i].row_count < 2)
			rows = cinema.sessions[i].row_count;
		for (int j = 0; j < rows * cinema.sessions[i].seats_in_a_row; ++j)
			if (!cinema.sessions[i].seats[j])
				++cnt;
	}
	else
	{
		for (int j = 2 * cinema.sessions[i].seats_in_a_row; j < cinema.sessions[i].row_count*cinema.sessions[i].seats_in_a_row; ++j)
			if (!cinema.sessions[i].seats[j])
				++cnt;
	}
	if (cnt < _request.seats_count)
		return 2;//Нет такого количества мест
	_request.hall_number = cinema.sessions[i].hall_number;
	return 0;//Запрос может быть удовлетворён
}

bool TicketOffice::Reserve(Request& _request)
{
	if (Check(_request))//Если нет свободных мест
		return false;
	int i = 0;
	while (i < cinema.count && (cinema.sessions[i].date != _request.date || cinema.sessions[i].film_name != _request.film_name || cinema.sessions[i].time_start != _request.time_start))
		++i;//Находим нужную сессию
	int cnt = _request.seats_count;
	if (_request.vip)
	{
		int rows = 2;
		if (cinema.sessions[i].row_count < 2)
			rows = cinema.sessions[i].row_count;
		for (int j = 0; j < rows * cinema.sessions[i].seats_in_a_row && cnt > 0; ++j)
			if (!cinema.sessions[i].seats[j])
			{
				cinema.sessions[i].seats[j] = 1;//Резервируем место
				--cnt;
			}
	}
	else
	{
		for (int j = 2 * cinema.sessions[i].seats_in_a_row; j < cinema.sessions[i].row_count*cinema.sessions[i].seats_in_a_row && cnt > 0; ++j)
			if (!cinema.sessions[i].seats[j])
			{
				cinema.sessions[i].seats[j] = 1;//Резервируем место
				--cnt;
			}
	}
	return true;
}

double TicketOffice::Calculate(const Request& _request) const
{
	//Пусть vip-места стоят в 1.5 раза дороже аналогичных обычных
	double multiply = 1;//Коэффициент умножения стоимости билета
	if (_request.vip)
		multiply *= 1.5;
	if (_request.time_start < 12 * 60 * 60)//Утренний сеанс
		multiply *= .75;
	else if (_request.time_start >= 18 * 60 * 60)//Вечерний сеанс
		multiply *= 1.5;
	int i = 0;
	while (i < cinema.count && (cinema.sessions[i].date != _request.date || cinema.sessions[i].film_name != _request.film_name || cinema.sessions[i].time_start != _request.time_start))
		++i;//Находим нужную сессию
	double one_seat_cost = cinema.sessions[i].cost * multiply;
	return one_seat_cost * _request.seats_count;
}

void TicketOffice::Cancel(const Request& _request)
{
	int i = 0;
	while (i < cinema.count && (cinema.sessions[i].date != _request.date || cinema.sessions[i].film_name != _request.film_name || cinema.sessions[i].time_start != _request.time_start))
		++i;//Находим нужную сессию
	int cnt = _request.seats_count;
	if (_request.vip)
	{
		int rows = 2;
		if (cinema.sessions[i].row_count < 2)
			rows = cinema.sessions[i].row_count;
		for (int j = 0; j < rows * cinema.sessions[i].seats_in_a_row && cnt > 0; ++j)
			if (cinema.sessions[i].seats[j] == 1)
			{
				cinema.sessions[i].seats[j] = 0;//Освобождаем место
				--cnt;
			}
	}
	else
	{
		for (int j = 2 * cinema.sessions[i].seats_in_a_row; j < cinema.sessions[i].row_count*cinema.sessions[i].seats_in_a_row && cnt > 0; ++j)
			if (cinema.sessions[i].seats[j] == 1)
			{
				cinema.sessions[i].seats[j] = 0;//Освобождаем место
				--cnt;
			}
	}
}

void TicketOffice::Set_date_and_time(const string& _date_today, const int& _current_time)
{
	date_today = _date_today;
	current_time = _current_time;
}