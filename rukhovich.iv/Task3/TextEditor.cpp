#include"TextEditor.h"
#include<iostream>
#include<Windows.h>

using namespace std;

//system("cls"); - ochistka ekrana
//SetConsoleCursorPosition() - ustanovka pozitsii kursora (Windows.h)
//COORD - struktura hraneniya koordinat (Windows.h)

TextEditor::TextEditor(const TextEditor& _te) : row(_te.row), cell(_te.cell), size(_te.size), text(_te.text) {}

TextEditor::TextEditor(int _row, int _cell, int _sz, string _text) : row(_row), cell(_cell), size(_sz), text(_text) {}

TextEditor::~TextEditor()
{
	row = 1;
	cell = 1;
	size = 0;
	text = "<empty>";
}

void TextEditor::SetSize(int _sz)
{
	size = _sz;
}

int TextEditor::GetSize()
{
	return size;
}

void TextEditor::SetPosition(int _row, int _cell)
{
	row = _row;
	cell = _cell;
}

void TextEditor::GetPosition(int* _row, int* _cell)
{
	*_row = row;
	*_cell = cell;
}

void TextEditor::Start()
{
	ShowMenu();
}

void TextEditor::ShowMenu()
{
	while (1)
	{
		system("cls");
		COORD c;
		c.X = 0;
		c.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		cout << "Welcome to my program!\nThese are the possible commands:\n";
		cout << "\"/set\" Set size and position of the Editor\n";
		cout << "\"/text\" Enter some text\n";
		cout << "\"/show\" Shows your last saved text\n";
		cout << "\"/exit\" Quit program\n";
		cout << "Your answer is: ";
		string ans;
		cin >> ans;
		if (ans == "/exit")
			return;
		if (ans == "/set")
		{
			cout << "Write the number of row, cell and size of the Editor\n";
			cin >> row >> cell >> size;
		}
		else if (ans == "/text")
		{
			ShowEditor();
		}
		else if (ans == "/show")
		{
			cout << "Your last text is: " << text;
			getchar();
			getchar();
		}
	}
}

void TextEditor::ShowEditor()
{
	while (1)
	{
		system("cls");
		COORD c;
		c.X = 0;
		c.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		cout << "You are in Editor now. Edit some text.\n";
		cout << "Use <Enter> to save your text. Only last message will be saved\n";
		cout << "Write \"/exit\" to return to the main menu\n";
		c.X = cell;
		c.Y = row + 3;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		string s;
		getline(cin, s);
		if (s == "/exit")
			return;
		if (s.size() > size)
			s.resize(size);
		text = s;
	}
}