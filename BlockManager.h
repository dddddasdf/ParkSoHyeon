#pragma once
#include"Block.h"
class BlockManager
{
private:
	Block* m_BlockWall;
	Block* m_Obstacle;
	Block* m_Feed;
	int m_iWallCount;
	int m_iFeedCount;
public:
	Position GetRandomPosition(int i);
	void SetRandObstacle();
	void DrawWallBlock();
	void InitFeed();	//���� ���� �ʱ�ȭ
	void AddFeed();	//���� �߰�
	void SetRandFeed();
	bool IsOverlap(int iXPos, int iYPos, int i);	//�ߺ� Ȯ��
	BlockManager();
	~BlockManager();
};
