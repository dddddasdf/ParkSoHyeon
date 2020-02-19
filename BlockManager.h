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
	void SetRandObstacle();	//방해물 랜덤 생성
	void DrawWallBlock();
	void InitFeed();	//먹이 배열 초기화
	void SetRandFeed(int i);	//먹이 생성
	bool IsOverlap(int iXPos, int iYPos, int i);	//중복 확인
	Position GetRandomPositionFeed();
	bool IsOverlapFeed(int iXPos, int iYPos);	//중복 확인 먹이 배치용
	int IsCollisionObject(int iSnakeX, int iSnakeY);	//충돌 체크
	void DeleteFeed(Block *DeleteFeed);	//먹은 먹이 없애기
	void DeleteBlocks();	//게임 종료할 때 블럭들 없애버리기
	BlockManager();
	~BlockManager();
};

