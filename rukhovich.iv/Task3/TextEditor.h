#pragma once
#include<string>

using namespace std;

class TextEditor
{
private:
	int row;//Nomer stroki
	int cell;//Nomer stolbtsa
	int size;//Razmer polya
	string text;//Text
	void ShowMenu();//Perehod v menu
	void ShowEditor();//Perehod v redaktor
public:
	TextEditor(const TextEditor& editor);//Constructor copyrovaniya
	TextEditor(int row = 0, int cell = 0, int size = 10, string text = "<empty>");//Konstructor po umolchaniyu + initsializacii
	~TextEditor();//Deconstruktor
	void SetSize(int size = 10);//Zadat' razmer polya redaktora
	int GetSize();//Uznat' razmer polya redaktora
	void SetPosition(int row, int cell);//Zadat' raspolozhenie redaktora
	void GetPosition(int* row, int* cell);//Uznat' raspolozhenie redaktora
	void Start();//Nachat' raboty s redaktotom
};