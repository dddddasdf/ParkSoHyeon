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
	int m_iDirectionState;
	int m_iOriginX, m_iOriginY;	//뱀 움직일 때 기존 좌표 저장용
	int m_iTmpX, m_iTmpY;	//뱀 머리가 움직일 좌표 임시 저장용
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
	void DeleteAfterimage(int x, int y);	//잔상 제거
	void GetSnakePosition(int *iSnakeX, int *iSnakeY);
	int IsCollisionBody();	//몸과 충돌했나 체크
	void InitSnakePosition();
	void KillSnake();
	void KillRecursion(SnakeInfo *TmpBody);	//재귀용으로 만듬,,
	void DeleteTmp();	//임시용 구조체 삭제
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Snake();
};

