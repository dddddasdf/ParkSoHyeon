#pragma once
#include"Block.h"
class BlockManager
{
private:
	Block* m_BlockWall;
	Block* m_Obstacle;
	Block* m_Feed;
	int m_iWallCount;
public:
	Position GetRandomPosition(int i);
	void SetRandObstacle();
	void DrawWallBlock();
	void AddFeed();	//먹이 추가
	void SetRandFeed();
	bool IsOverlap(int iXPos, int iYPos, int i);	//중복 확인
	BlockManager();
	~BlockManager();
};

