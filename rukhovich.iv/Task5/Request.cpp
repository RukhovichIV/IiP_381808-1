#include"Request.h"

Request::Request()
{
	date = "01.01.1900";
	time_start = 0;
	film_name = "<empty>";
	vip = 0;
	seats_count = 0;
}

Request::Request(const Request& _request)
{
	date = _request.date;
	time_start = _request.time_start;
	film_name = _request.film_name;
	vip = _request.vip;
	seats_count = _request.seats_count;
}

Request::Request(string _date, int _time_start,
	string _film_name,
	bool _vip, int _seats_count)
{
	date = _date;
	time_start = _time_start;
	film_name = _film_name;
	vip = _vip;
	seats_count = _seats_count;
}

Request::~Request()
{
	date = "01.01.1900";
	time_start = 0;
	film_name = "<empty>";
	vip = 0;
	seats_count = 0;
}