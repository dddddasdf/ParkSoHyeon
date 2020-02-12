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
	void InitFeed();	//먹이 개수 초기화
	void AddFeed();	//먹이 추가
	void SetRandFeed();
	bool IsOverlap(int iXPos, int iYPos, int i);	//중복 확인
	BlockManager();
	~BlockManager();
};

