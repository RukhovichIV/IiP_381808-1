#pragma once
#include<iostream>

using namespace std;

class Field//Хранит в себе структуру поля боя
{
private:
	//a-j - номер корабля в данной клетке, A-J - номер поражённого корабля в данной клетке, · - промах, _ - пустая клетка
	char** field;

	//Количество "целых" клеток у каждого корабля
	int* ships;

	//Количество "целых" кораблей
	int ship_count;

	//Нужно ли скрывать ненайденные корабли на поле
	bool is_private;
public:
	//Конструктор по умолчанию
	Field(bool is_private = false);

	//Конструктор копирования
	Field(const Field& field);

	//Деструктор
	~Field();

	//Проверка клетки на пустоту
	int IsEmpty(const int& x, const int& y) const;

	//Выстрел по клетке
	int Shoot(const int& x, const int& y);

	//Заполняет поле компьютера кораблями
	void FillShips();

	//Ставит корабль корабль длины len в координаты x, y с направлением dir, или возвращает false
	bool PutAShip(int x, int y, int dir, int len);

	//Отрисовка поля на экране
	friend ostream& operator<<(ostream& stream, const Field& field);
};