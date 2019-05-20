#include<iostream>
#include<Windows.h>
#include<ctime>
#include"Field.h"

using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Вас приветствует программа \"Морской бой\"\nЧтобы начать игру, нажмите любую клавишу";
	getchar();
	Field player_field = Field(), enemy_field = Field(true);
	enemy_field.FillShips();
	int lens[10] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 };//Размеры кораблей

	for (int i = 0; i < 10; ++i)//Постановка кораблей
	{
		while (1)
		{
			system("cls");
			cout << player_field << enemy_field;
			cout << "Введите клетку, в которую требуется поставить корабль длины " << lens[i];
			cout << "\nВ формате <строка> <столбец> <направление> (0 - вверх, 1 - вправо, 2 - вниз, 3 - влево) ";
			char row;
			int col, dir;
			srand(time(0));
			cin >> row >> col >> dir;
			if (player_field.PutAShip(row - 'A' + 1, col, dir, lens[i]))
				break;
			else
			{
				cout << "Нельзя поставить корабль так\n";
				getchar();
				getchar();
			}
		}
	}

	while (1)
	{
		while (1)//Ход игрока
		{
			system("cls");
			cout << player_field << enemy_field;
			cout << "Выберите клетку для стрельбы в формате <строка> <столбец>: ";
			int x, y;
			char c;
			cin >> c >> y;
			x = c - 'A' + 1;
			int res = enemy_field.IsEmpty(x, y);
			if (!res)
			{
				cout << "Не существует такой клетки\n";
				getchar();
				getchar();
			}
			else if (res == 1)
			{
				cout << "В эту клетку уже стреляли\n";
				getchar();
				getchar();
			}
			else
			{
				res = enemy_field.Shoot(x, y);
				if (!res)
				{
					cout << "Промах!\n";
					getchar();
					getchar();
					break;
				}
				else if (res == 1)
					cout << "Попадание\n";
				else if (res == 2)
					cout << "Корабль утотплен!\n";
				else
				{
					cout << "Победа. Игра окончена";
					return 0;
				}
				getchar();
				getchar();
			}
		}
		while (1)//Ход компьютера
		{
			system("cls");
			cout << player_field << enemy_field;
			srand(time(0));
			int x = rand() % 10 + 1, y = rand() % 10 + 1;
			while (player_field.IsEmpty(x, y) != 2)
			{
				x = rand() % 10 + 1;
				y = rand() % 10 + 1;
			}
			cout << "Компьютер стреляет: " << char(x + 'A' - 1) << ' ' << y << '\n';
			int res = player_field.Shoot(x, y);
			if (!res)
			{
				cout << "Промах!\n";
				getchar();
				getchar();
				break;
			}
			else if (res == 1)
				cout << "Попадание\n";
			else if (res == 2)
				cout << "Корабль утотплен!\n";
			else
			{
				cout << "Компьютер побеждает. Игра окончена";
				return 0;
			}
			getchar();
			getchar();
		}
	}
	return 0;
}