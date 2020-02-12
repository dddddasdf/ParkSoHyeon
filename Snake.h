#pragma once
#include "headers.h"
#include "Block.h"

struct SnakeInfo
{
	int iXPos;
	int iYPos;
	bool isHead;
	SnakeInfo *Next;
	Block Block_Snake;
};

class Snake
{
private:
	int m_iLife;
	int m_iDirectionState;
	int m_iSpeedControl;
	SnakeInfo *Head, *Body, *tmp;
public:
	Snake();
	void PrintSnake();
	void CreateBody();
	void MoveSnake();
	void MoveBody(SnakeInfo *tmp);
	void KillSnake();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Snake();
};

