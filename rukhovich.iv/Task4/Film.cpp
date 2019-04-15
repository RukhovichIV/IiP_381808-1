#include"Film.h"
#include<string>

using namespace std;

Film::Film(const string& _name,
	const string& _director,
	const string& _scriptwriter,
	const string& _composer,
	const string& _date,
	const int _year,
	const long long _gross) : name(_name), director(_director),
	scriptwriter(_scriptwriter), composer(_composer), date(_date),
	year(_year), gross(_gross) {}

Film::Film(const Film& _film) : name(_film.name), director(_film.director),
scriptwriter(_film.scriptwriter), composer(_film.composer), date(_film.date),
year(_film.year), gross(_film.gross) {}

Film::~Film()
{
	name = "<unknown>";
	director = "<unknown>";
	scriptwriter = "<unknown>";
	composer = "<unknown>";
	date = "01.01.1800";
	year = 1800;
	gross = 0;
}

bool Film::operator<(const Film& _film) const
{
	if (name == _film.name)
		return year < _film.year;
	return name < _film.name;
}

bool Film::operator>(const Film& _film) const
{
	return _film < *this;
}

bool Film::operator==(const Film& _film) const
{
	return name == _film.name && year == _film.year;
}

bool Film::operator!=(const Film& _film) const
{
	return !(*this == _film);
}

Film& Film::operator=(const Film& _film)
{
	name = _film.name;
	director = _film.director;
	scriptwriter = _film.scriptwriter;
	composer = _film.composer;
	date = _film.date;
	year = _film.year;
	gross = _film.gross;
	return *this;
}