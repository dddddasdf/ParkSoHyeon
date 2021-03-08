#pragma once
#include "headers.h"
#include "Block.h"
#include "Headers (2).h"

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
	int m_iOriginX, m_iOriginY;	//¹ì ¿òÁ÷ÀÏ ¶§ ±âÁ¸ ÁÂÇ¥ ÀúÀå¿ë
	int m_iTmpX, m_iTmpY;	//¹ì ¸Ó¸®°¡ ¿òÁ÷ÀÏ ÁÂÇ¥ ÀÓ½Ã ÀúÀå¿ë
	SnakeInfo *Head, *Body;
	Position HeadPosition;
	Position Bodytmp;
public:
	Snake();
	void PrintSnake();
	void CreateBody();
	void MoveSnake();
	void MoveBody(SnakeInfo *tmp);
	void ChangeDirection(int iDirection);
	void DeleteAfterimage(int x, int y);	//ÀÜ»ó Á¦°Å
	void GetSnakePosition(int *iSnakeX, int *iSnakeY);
	int IsCollisionBody();	//¸ö°ú Ãæµ¹Çß³ª Ã¼Å©
	void InitSnakePosition();
	void KillSnake();
	void KillRecursion(SnakeInfo *TmpBody);	//Àç±Í¿ëÀ¸·Î ¸¸µë,,

	~Snake();
};

