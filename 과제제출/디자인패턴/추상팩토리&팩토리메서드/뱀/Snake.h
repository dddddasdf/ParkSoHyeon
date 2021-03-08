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
	int m_iOriginX, m_iOriginY;	//�� ������ �� ���� ��ǥ �����
	int m_iTmpX, m_iTmpY;	//�� �Ӹ��� ������ ��ǥ �ӽ� �����
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
	void DeleteAfterimage(int x, int y);	//�ܻ� ����
	void GetSnakePosition(int *iSnakeX, int *iSnakeY);
	int IsCollisionBody();	//���� �浹�߳� üũ
	void InitSnakePosition();
	void KillSnake();
	void KillRecursion(SnakeInfo *TmpBody);	//��Ϳ����� ����,,

	~Snake();
};

