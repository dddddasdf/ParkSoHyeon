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
	int m_ix;
	int m_iy;
	bool m_bLiveStatus;
public:
	Block();
	void SetBlock(BLOCK_ATTRIBUTE Attribute, Position P);
	void DrawBlock();
	int GetPosition(int Pos);
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Block();
};

