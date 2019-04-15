#include"FilmLibrary.h"
#include<string>

FilmLibrary::FilmLibrary(int _reserved) : size(0)
{
	lib = new Film[_reserved];
}

FilmLibrary::FilmLibrary(const FilmLibrary& _lib) : size(_lib.size), reserved(_lib.reserved)
{
	lib = new Film[reserved];
	for (int i = 0; i < size; ++i)
		lib[i] = _lib.lib[i];
}

FilmLibrary::~FilmLibrary()
{
	delete[] lib;
	size = 0;
	reserved = 0;
}

bool FilmLibrary::AddFilm(const string& _name,
	const string& _director,
	const string& _scriptwriter,
	const string& _composer,
	const string& _date,
	const long long _gross)
{
	int year = stoi(_date.substr(6,4));
	Film f = Film(_name, _director, _scriptwriter, _composer, _date, year, _gross);
	int i = 0;
	while (i < size && lib[i] < f)
		++i;
	if (lib[i] == f)//Такой фильм уже есть
		return false;
	if (size < reserved)//Если ещё есть место под новые фильмы
	{
		for (int j = size; j > i; --j)
			lib[j] = lib[j - 1];
		lib[i] = f;
	}
	else
	{
		Film* new_lib = new Film[reserved + 10];
		memcpy(new_lib, lib, sizeof(Film)*i);
		memcpy(new_lib + i + 1, lib + i, sizeof(Film)*(size - i));
		new_lib[i] = f;
		delete[] lib;
		lib = new_lib;
		reserved += 10;
	}
	++size;
	return true;
}

bool FilmLibrary::ChangeFilm(const string& _name,
	const int _year,
	const string& _new_name,
	const string& _director,
	const string& _scriptwriter,
	const string& _composer,
	const string& _date,
	const long long _gross)
{
	Film f = Film(_name, _director, _scriptwriter, _composer, _date, _year, _gross);
	int i = FindFilm(_name, _year);
	if (i == -1)//Такого фильма не существует
		return false;
	f.name = _new_name;
	f.year = stoi(f.date.substr(6, 4));
	lib[i] = f;
	return true;
}

bool FilmLibrary::DeleteFilm(const string& _name,
	const int _year) 
{
	int i = FindFilm(_name, _year);
	if (i == -1)//Такого фильма не существует
		return false;
	for (int j = i + 1; j < size; ++j)
		lib[j - 1] = lib[j];
	--size;
	return true;
}

int FilmLibrary::FindFilm(const string& _name,
	const int _year) const
{
	Film f = Film(_name, "", "", "", "", _year, 0);
	int i = 0;
	while (i < size && lib[i] < f)
		++i;
	if (i == size || lib[i] != f)//Такого фильма нет
		return -1;
	return i;
}

void FilmLibrary::FindAllFilms(const string& _director,
	int* _films,
	const int _max_count) const
{
	int pos = 0;
	for(int i = 0; i < size; ++i)
		if (lib[i].director == _director)
		{
			if (pos == _max_count)
				return;
			_films[pos] = i;
			++pos;
		}
}

void FilmLibrary::FindAllFilms(const int _year,
	int* _films,
	const int _max_count) const
{
	int pos = 0;
	for (int i = 0; i < size; ++i)
		if (lib[i].year == _year)
		{
			if (pos == _max_count)
				return;
			_films[pos] = i;
			++pos;
		}
}

struct mypair
{
	long long gross;
	int number;
};

void MergeSort(mypair* pairs, int l, int r)
{
	if (l == r)
		return;
	int m = (l + r) >> 1;
	MergeSort(pairs, l, m);
	MergeSort(pairs, m + 1, r);
	mypair* new_arr = new mypair[r - l + 1];
	int i = l, j = m + 1, pos = 0;
	while (i <= m && j <= r)
	{
		if (pairs[i].gross > pairs[j].gross)
		{
			new_arr[pos] = pairs[i];
			++i;
		}
		else
		{
			new_arr[pos] = pairs[j];
			++j;
		}
		++pos;
	}
	while (i <= m)
	{
		new_arr[pos] = pairs[i];
		++i;
		++pos;
	}
	while (j <= r)
	{
		new_arr[pos] = pairs[j];
		++j;
		++pos;
	}
	memcpy(pairs + l, new_arr, r - l + 1);
	delete[] new_arr;
}

void FilmLibrary::FindAllFilmsByGross(int* _films,
	const int _max_count,
	const int _year) const
{
	mypair* pairs = new mypair[size];
	int cnt = 0;
	for (int i = 0; i < size; ++i)
		if (_year)//Фильмы, вышедшие в данном году
		{
			if (lib[i].year == _year)
			{
				pairs[i].gross = lib[i].gross;
				pairs[i].number = i;
				++cnt;
			}
		}
		else//По всем годам
		{
			pairs[i].gross = lib[i].gross;
			pairs[i].number = i;
			++cnt;
		}
	MergeSort(pairs, 0, cnt - 1);
	for (int i = 0; i < _max_count && i < cnt; ++i)
		_films[i] = pairs[i].number;
}

int FilmLibrary::GetCount() const
{
	return size;
}

ostream& operator<<(ostream& _stream, const FilmLibrary& _library)
{
	_stream << _library.size << '\n';
	for (int i = 0; i < _library.size; ++i)
		_stream << _library.lib[i].name << '\n'
		<< _library.lib[i].director << '\n'
		<< _library.lib[i].scriptwriter << '\n'
		<< _library.lib[i].composer << '\n'
		<< _library.lib[i].date << '\n'
		<< _library.lib[i].gross << "\n\n";
	return _stream;
}

istream& operator>>(istream& _stream, FilmLibrary& _library)
{
	if (_library.reserved > 0)//Если в библиотеке что-то было
		delete[] _library.lib;
	_stream >> _library.size;
	_library.reserved = _library.size + 10;
	_library.lib = new Film[_library.reserved];
	string tmp;
	for (int i = 0; i < _library.size; ++i)
	{
		getline(_stream, tmp);//Считываем пустую (разделительную) строку
		getline(_stream, _library.lib[i].name);
		getline(_stream, _library.lib[i].director);
		getline(_stream, _library.lib[i].scriptwriter);
		getline(_stream, _library.lib[i].composer);
		getline(_stream, _library.lib[i].date);
		_library.lib[i].year = stoi(_library.lib[i].date.substr(6, 4));//Высчитываем год в числовом виде
		getline(_stream, tmp);
		_library.lib[i].gross = stoi(tmp);
	}
	return _stream;
}