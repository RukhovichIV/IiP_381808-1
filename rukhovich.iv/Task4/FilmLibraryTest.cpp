#include"FilmLibrary.h"
#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;

int main()
{
//#define debug
#ifdef debug
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FilmLibrary library;
	while (1)
	{
		system("cls");
		cout << "Фильмотека. Версия 1. ННГУ 2019.\n\n";
		cout << "Добро пожаловать в программу Фильмотека!\n";
		cout << "Вот список возможных команд: \n";
		cout << "\"/read <filename>\"\t\t\t Считать Фильмотеку из текстового файла\n";
		cout << "\"/write <filename>\"\t\t\t Вывести Фильмотеку в текстовый файл\n";
		cout << "\"/show\"\t\t\t\t\t Вывести Фильмотеку в консоль\n";
		cout << "\"/add <parameters>\"\t\t\t Добавить фильм в Фильмотеку\n";
		cout << "\"/change <name, year, parameters>\"\t Изменить параметры фильма с данным названием, вышедшего в данном году\n";
		cout << "\"/delete <name, year>\"\t\t\t Удалить фильм из Фильмотеки (по названию и году выпуска)\n";
		cout << "\"/find <name, year>\"\t\t\t Найти фильм (по названию и году выпуска)\n";
		cout << "\"/find_by_director <director, max_count>\"\t\t Найти все фильмы данного режиссёра\n";
		cout << "\"/find_by_year <year, max_count>\"\t\t\t Найти все фильмы, выпущенные в данном году\n";
		cout << "\"/find_by_gross <max_count>\"\t\t Найти первые max_count фильмов с самой большой выручкой\n";
		cout << "\"/find_by_gross_year <max_count, year>\"\t Найти первые max_count фильмов с самой большой выручкой, выпущенных в данном году\n";
		cout << "\"/count\"\t\t\t\t Узнать текущее количество фильмов в Фильмотеке\n";
		cout << "\"/exit\"\t\t\t\t\t Завершить работу в программе\n";
		cout << "Ваш ответ: ";
		string ans;
		cin >> ans;
		if (ans == "/exit")
			break;
		if (ans == "/read")
		{
			string path;
			cin >> path;
			ifstream fin(path, ios_base::in);
			fin >> library;
			fin.close();
			cout << "Успешно";
			getchar();
			getchar();
		}
		else if (ans == "/write")
		{
			string path;
			cin >> path;
			ofstream fout(path, ios_base::out);
			fout << library;
			fout.close();
			cout << "Успешно";
			getchar();
			getchar();
		}
		else if (ans == "/show")
		{
			cout << library;
			getchar();
			getchar();
		}
		else if (ans == "/add")
		{
			string name, director, scriptwriter, composer, date;
			long long gross;
			getline(cin, name);
			getline(cin, name);
			getline(cin, director);
			getline(cin, scriptwriter);
			getline(cin, composer);
			getline(cin, date);
			cin >> gross;
			if (library.AddFilm(name, director, scriptwriter, composer, date, gross))
				cout << "Успешно";
			else
				cout << "Такой фильм уже имеется";
			getchar();
			getchar();
		}
		else if (ans == "/change")
		{
			string fname, name, director, scriptwriter, composer, date;
			long long gross;
			int fyear;
			getline(cin, fname);
			getline(cin, fname);
			getline(cin, name);
			fyear = stoi(name);
			getline(cin, name);
			getline(cin, director);
			getline(cin, scriptwriter);
			getline(cin, composer);
			getline(cin, date);
			cin >> gross;
			if (library.ChangeFilm(fname, fyear, name, director, scriptwriter, composer, date, gross))
				cout << "Успешно";
			else
				cout << "Такого фильма не существует";
			getchar();
			getchar();
		}
		else if (ans == "/delete")
		{
			string fname;
			int fyear;
			getline(cin, fname);
			getline(cin, fname);
			cin >> fyear;
			if(library.DeleteFilm(fname, fyear))
				cout << "Успешно";
			else
				cout << "Такого фильма не существует";
			getchar();
			getchar();
		}
		else if (ans == "/find")
		{
			string fname;
			int fyear;
			getline(cin, fname);
			getline(cin, fname);
			cin >> fyear;
			int i = library.FindFilm(fname, fyear);
			if (i>=0)
				cout << "Фильм находится на позиции " << i + 1 << " в Фильмотеке";
			else
				cout << "Такого фильма не существует";
			getchar();
			getchar();
		}
		else if (ans == "/find_by_director")
		{
			string director;
			int max_count;
			getline(cin, director);
			getline(cin, director);
			cin >> max_count;
			int* films = new int[max_count + 1];
			for (int i = 0; i <= max_count; ++i)
				films[i] = -1;
			library.FindAllFilms(director, films, max_count);
			int i = 0;
			cout << "Фильмы режиссера " << director << " находятся в Фильмотеке под номерами: ";
			while (films[i] != -1)
				cout << films[i++] + 1 << ' ';
			cout << '\n';
			getchar();
			getchar();
			delete[] films;
		}
		else if (ans == "/find_by_year")
		{
			int year;
			int max_count;
			cin >> year >> max_count;
			int* films = new int[max_count + 1];
			for (int i = 0; i <= max_count; ++i)
				films[i] = -1;
			library.FindAllFilms(year, films, max_count);
			int i = 0;
			cout << "Фильмы, вышедшие в " << year << " находятся в Фильмотеке под номерами: ";
			while (films[i] != -1)
				cout << films[i++] + 1 << ' ';
			cout << '\n';
			getchar();
			getchar();
			delete[] films;
		}
		else if (ans == "/find_by_gross")
		{
			int max_count;
			cin >> max_count;
			int* films = new int[max_count + 1];
			for (int i = 0; i <= max_count; ++i)
				films[i] = -1;
			library.FindAllFilmsByGross(films, max_count);
			int i = 0;
			cout << "Номера фильмов в порядке убывания общей прибыли: ";
			while (films[i] != -1)
				cout << films[i++] + 1 << ' ';
			cout << '\n';
			getchar();
			getchar();
			delete[] films;
		}
		else if (ans == "/find_by_gross_year")
		{
			int max_count, year;
			cin >> max_count >> year;
			int* films = new int[max_count + 1];
			for (int i = 0; i <= max_count; ++i)
				films[i] = -1;
			library.FindAllFilmsByGross(films, max_count, year);
			int i = 0;
			cout << "Номера фильмов, вышедших в " << year << " в порядке убывания общей прибыли: ";
			while (films[i] != -1)
				cout << films[i++] + 1 << ' ';
			cout << '\n';
			getchar();
			getchar();
			delete[] films;
		}
		else if (ans == "/count")
		{
			cout << "На данный момент в Фильмотеке находится " << library.GetCount() << " фильмов\n";
			getchar();
			getchar();
		}
	}
	return 0;
}