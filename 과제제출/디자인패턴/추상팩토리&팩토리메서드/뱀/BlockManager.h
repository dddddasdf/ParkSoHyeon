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

	WallBlockFactory *NewWallBlockFactory;
	FeedBlockFactory *NewFeedBlockFactory;
	ObstacleBlockFactory *NewObstacleBlockFactory;

	std::vector <Block*> m_WallBlockVector;
	std::vector <Block*> m_FeedBlockVector;
	std::vector <Block*> m_ObstacleBlockVector;

	int m_iWallCount;

	int m_iCurrentFeedCount;
	bool m_bIsCountedMaxFeed;	//먹이 주는데 사용

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
	void DeleteBlocks();	//블럭들 동적 할당 해제
	void DeleteWallBlocks();	//벽 블럭들 동적 할당 해제 
	BlockManager();
	~BlockManager();
};

//매니저에 추상팩토리 적용하는 건 했음
//근데 팩토리메소드는 어디다 써먹지