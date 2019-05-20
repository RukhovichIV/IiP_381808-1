#include<ctime>
#include"Field.h"

//Конструктор по умолчанию
Field::Field(bool _is_private)
{
	field = new char*[12];
	for (int i = 0; i < 12; ++i)
	{
		field[i] = new char[12];
		for (int j = 0; j < 12; ++j)
			field[i][j] = '_';
	}
	ships = new int[10]{ 1,1,1,1,2,2,2,3,3,4 };
	ship_count = 0;
	is_private = _is_private;
}

//Конструктор копирования
Field::Field(const Field& _field)
{
	field = new char*[12];
	for (int i = 0; i < 12; ++i)
	{
		field[i] = new char[12];
		for (int j = 0; j < 12; ++j)
			field[i][j] = _field.field[i][j];
	}
	ships = new int[10];
	for (int i = 0; i < 10; ++i)
		ships[i] = _field.ships[i];
	ship_count = _field.ship_count;
	is_private = _field.is_private;
}

//Деструктор
Field::~Field()
{
	for (int i = 0; i < 12; ++i)
		delete[] field[i];
	delete[] field;
	delete[] ships;
	ship_count = 0;
	is_private = false;
}

//Проверка клетки на пустоту
int Field::IsEmpty(const int& _x, const int& _y) const
{
	if (_x < 1 || _x > 10 || _y < 1 || _y > 10)
		return 0;//Не существует такой клетки
	return (field[_x][_y] == '_' || (field[_x][_y] >= 'a' && field[_x][_y] <= 'j') ? 2 : 1);
}

//Массивы для сдвига указателя
const int dx[8]{ 0, 1, 1, 1, 0, -1, -1, -1 };
const int dy[8]{ 1, 1, 0, -1, -1, -1, 0, 1 };

//Выстрел по клетке
int Field::Shoot(const int& _x, const int& _y)
{
	if (field[_x][_y] == '_')
	{
		field[_x][_y] = '·';
		return 0;//Промах
	}
	int ship = field[_x][_y] - 'a';
	field[_x][_y] += 'A' - 'a';
	ships[ship]--;
	if (ships[ship] == 0)
	{
		for (int i = 1; i <= 10; ++i)
			for (int j = 1; j <= 10; ++j)
				if (field[i][j] - 'A' == ship)
					for (int k = 0; k < 8; ++k)
						if (field[i + dx[k]][j + dy[k]] == '_')
							field[i + dx[k]][j + dy[k]] = '·';
		ship_count--;
		if (!ship_count)
			return 3;//Победа
		return 2;//Корабль утоплен
	}
	return 1;//Попадание
}

//Заполняет поле компьютера кораблями
void Field::FillShips()
{
	srand(time(0));
	for (int i = 0; i < 10; ++i)
		while (!PutAShip(rand() % 10 + 1, rand() % 10 + 1, rand() % 4, ships[i])) {}
}

//Массивы для сдвига указателя
const int d2x[4]{ 0, 1, 0, -1 };
const int d2y[4]{ 1, 0, -1, 0 };

//Ставит корабль корабль в координаты x, y с направлением dir, или возвращает false
bool Field::PutAShip(int _x, int _y, int _dir, int _len)
{
	for (int i = 0; i < _len; ++i)//Проверяем, можем ли поставить
	{
		int cx = _x + i*d2x[_dir];
		int cy = _y + i*d2y[_dir];
		if (cx < 1 || cy < 1 || cx > 10 || cy > 10)
			return false;
		if (field[cx][cy] != '_')
			return false;
		for (int j = 0; j < 8; ++j)
			if (field[cx + dx[j]][cy + dy[j]] != '_')
				return false;
	}
	for (int i = 0; i < _len; ++i)//Ставим
	{
		int cx = _x + i*d2x[_dir];
		int cy = _y + i*d2y[_dir];
		field[cx][cy] = 'a' + ship_count;
	}
	++ship_count;
	return true;
}

//Отрисовка поля на экране
ostream& operator<<(ostream& _stream, const Field& _field)
{//EN - Enemy, PL - Player
	_stream << (_field.is_private? "EN" : "PL") << " 1 2 3 4 5 6 7 8 9 10";
	for (int i = 1; i <= 10; ++i)
	{
		_stream << '\n' << char('A' + i - 1) << ' ';
		for (int j = 1; j <= 10; ++j)
		{
			_stream << '|';
			if (_field.field[i][j] >= 'a' && _field.field[i][j] <= 'j')
				_stream << (_field.is_private ? '_' : _field.field[i][j]);
			else if (_field.field[i][j] == '·' || _field.field[i][j] == '_')
				_stream << _field.field[i][j];
			else
				_stream << 'X';
		}
		_stream << '|';
	}
	_stream << '\n' << _field.ship_count << endl;
	return _stream;
}