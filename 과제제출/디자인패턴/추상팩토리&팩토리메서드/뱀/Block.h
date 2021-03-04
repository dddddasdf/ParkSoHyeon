#pragma once
#include "headers.h"

struct Position
{
	int m_ix;
	int m_iy;
};

class Block
{
private:
	BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;
public:
	Block();
	void SetBlock(BLOCK_ATTRIBUTE Attribute, Position P);
	void DrawBlock();
	void DeleteBlock(int x, int y);
	int GetPosition(int Pos);
	void DeletePosition();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Block();
};

