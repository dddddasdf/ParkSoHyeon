#pragma once
#include "headers.h"
#include "Block.h"

struct SnakeInfo
{
	int iXPos;
	int iYPos;
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
	Position HeadPosition;
	Position Bodytmp;
public:
	Snake();
	void PrintSnake();
	void CreateBody();
	void MoveSnake();
	void MoveBody(SnakeInfo *tmp);
	void ChangeDirection(int iDirection);
	void DeleteAfterimage(int x, int y);	//¿‹ªÛ ¡¶∞≈
	void GetSnakePosition(int *iSnakeX, int *iSnakeY);
	void InitSnakePosition();
	void KillSnake();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Snake();
};

