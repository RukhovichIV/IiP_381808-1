#pragma once
#include"Film.h"
#include<iostream>

class FilmLibrary
{
private:
	Film* lib;//Фильмотека
	int size;//Количество фильмов
	int reserved;//Количество зарезервированных мест под фильмы
public:
	FilmLibrary(int reserved = 10);//Конструктор по умолчанию и инициализации
	FilmLibrary(const FilmLibrary& lib);//Конструктор копирования
	~FilmLibrary();//Деструктор
	bool AddFilm(const string& name = "<unknown>",//Добавление нового фильма
		const string& director = "<unknown>",
		const string& scriptwriter = "<unknown>",
		const string& composer = "<unknown>",
		const string& date = "01.01.1800",
		const long long gross = 0);
	bool ChangeFilm(const string& name,//Изменение существующего фильма
		const int year,
		const string& new_name = "<unknown>",
		const string& director = "<unknown>",
		const string& scriptwriter = "<unknown>",
		const string& composer = "<unknown>",
		const string& date = "01.01.1800",
		const long long gross = 0);
	bool DeleteFilm(const string& name,//Удаление фильма
		const int year);
	int FindFilm(const string& name,//Поиск фильма по названию и году выпуска
		const int year) const;
	void FindAllFilms(const string& director,//Поиск всех фильмов, снятых данным режиссером
		int* films,
		const int max_count) const;
	void FindAllFilms(const int year,//Поиск всех фильмов, вышедших в данном году
		int* films,
		const int max_count) const;
	void FindAllFilmsByGross(int* films,//Поиск фильмов, упорядоченных по суммарной прибыли, вышедших в данном или любом году
		const int max_count,
		const int year = 0) const;
	int GetCount() const;//Количество фильмов в Фильмотеке
	friend ostream& operator<<(ostream& stream,//Перегрузка вывода
		const FilmLibrary& library);
	friend istream& operator>>(istream& stream,//Перегрузка ввода
		FilmLibrary& library);
};