#pragma once
#include"Block.h"
#include "Headers (2).h"
#include "BlockFactory.h"


class BlockManager
{
private:
	Block* m_BlockWall;
	Block* m_Obstacle;
	Block* m_Feed;
	int m_iWallCount;
public:
	Position GetRandomPosition(int i);
	void SetRandObstacle();	//���ع� ���� ����
	void DrawWallBlock();
	void InitFeed();	//���� �迭 �ʱ�ȭ
	void SetRandFeed(int i);	//���� ����
	bool IsOverlap(int iXPos, int iYPos, int i);	//�ߺ� Ȯ��
	Position GetRandomPositionFeed();
	bool IsOverlapFeed(int iXPos, int iYPos);	//�ߺ� Ȯ�� ���� ��ġ��
	int IsCollisionObject(int iSnakeX, int iSnakeY);	//�浹 üũ
	void DeleteFeed(Block *DeleteFeed);	//���� ���� ���ֱ�
	BlockManager();
	~BlockManager();
};

