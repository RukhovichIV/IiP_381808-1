#include"Session.h"

Session::Session() 
{
	date = "01.01.1900";
	time_start = 0;
	film_name = "<empty>";
	hall_number = 1;
	cost = 0;
	row_count = 0;
	seats_in_a_row = 0;
	seats = nullptr;
}

Session::Session(const Session& _session)
{
	date = _session.date;
	time_start = _session.time_start;
	film_name = _session.film_name;
	hall_number = _session.hall_number;
	cost = _session.cost;
	row_count = _session.row_count;
	seats_in_a_row = _session.seats_in_a_row;
	seats = new char[row_count*seats_in_a_row];
	for (int i = 0; i < row_count*seats_in_a_row; ++i)
		seats[i] = _session.seats[i];
}

Session::Session(const string& _date, const int& _time_start,
	const string& _film_name, const int& _hall_number,
	const int& _cost, const int& _row_count, const int& _seats_in_a_row)
{
	date = _date;
	time_start = _time_start;
	film_name = _film_name;
	hall_number = _hall_number;
	cost = _cost;
	row_count = _row_count;
	seats_in_a_row = _seats_in_a_row;
	seats = new char[row_count*seats_in_a_row];
	memset(seats, 0, sizeof(seats));
}

Session::~Session()
{
	date = "01.01.1900";
	time_start = 0;
	film_name = "<empty>";
	hall_number = 1;
	cost = 0;
	row_count = 0;
	seats_in_a_row = 0;
	delete[] seats;
}

istream& operator>>(istream& _stream, Session& _session)
{
	string tmp;
	getline(_stream, tmp);
	_session.date = tmp;
	getline(_stream, tmp);
	_session.time_start = stoi(tmp);
	getline(_stream, tmp);
	_session.film_name = tmp;
	getline(_stream, tmp);
	_session.hall_number = stoi(tmp);
	getline(_stream, tmp);
	_session.cost = stoi(tmp);
	getline(_stream, tmp);
	_session.row_count = stoi(tmp);
	getline(_stream, tmp);
	_session.seats_in_a_row = stoi(tmp);
	return _stream;
}
