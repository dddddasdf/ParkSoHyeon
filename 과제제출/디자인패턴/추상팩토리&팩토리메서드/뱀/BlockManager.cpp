#include "BlockManager.h"

#define NOT_EXSIT_FEED -10

BlockManager::BlockManager()
{
	NewWallBlockFactory = new WallBlockFactory();
	

	//벽 생성-기존
	/*m_iWallCount = ((MAP_WIDTH * 2) + (MAP_HEIGHT * 2)) - 4;
	m_BlockWall = new Block[m_iWallCount];
	int Count = 0;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		Position tmp = { i,0 };
		m_BlockWall[Count++].SetBlock(BLOCK_ATTRIBUTE_WALL, tmp);
	}
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		Position tmp = { i,MAP_HEIGHT - 1 };
		m_BlockWall[Count++].SetBlock(BLOCK_ATTRIBUTE_WALL, tmp);
	}
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		Position tmp = { 0,i };
		m_BlockWall[Count++].SetBlock(BLOCK_ATTRIBUTE_WALL, tmp);
	}
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		Position tmp = { MAP_WIDTH - 1 ,i };
		m_BlockWall[Count++].SetBlock(BLOCK_ATTRIBUTE_WALL, tmp);
	}*/
	m_Obstacle = NULL;
	m_Feed = NULL;

	//벽 생성-팩토리 적용
	m_iWallCount = ((MAP_WIDTH * 2) + (MAP_HEIGHT * 2)) - 4;
	int iCount = 0;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		Position tmp = { i,0 };
		Block *NewWallBlock = NewWallBlockFactory->CreateNewBlockClass();
		NewWallBlock->SetBlockPosition(tmp);
		m_WallBlockVector.push_back(NewWallBlock);
	}
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		Position tmp = { i,MAP_HEIGHT - 1 };
		Block *NewWallBlock = NewWallBlockFactory->CreateNewBlockClass();
		NewWallBlock->SetBlockPosition(tmp);
		m_WallBlockVector.push_back(NewWallBlock);
	}
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		Position tmp = { 0,i };
		Block *NewWallBlock = NewWallBlockFactory->CreateNewBlockClass();
		NewWallBlock->SetBlockPosition(tmp);
		m_WallBlockVector.push_back(NewWallBlock);
	}
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		Position tmp = { MAP_WIDTH - 1 ,i };
		Block *NewWallBlock = NewWallBlockFactory->CreateNewBlockClass();
		NewWallBlock->SetBlockPosition(tmp);
		m_WallBlockVector.push_back(NewWallBlock);
	}
	
}

bool BlockManager::IsOverlap(int iXPos, int iYPos, int i)
{
	for (int x = 0; x < i; x++)
	{
		//if (m_Obstacle[x].GetPosition(POSITION_X) == iXPos && m_Obstacle[x].GetPosition(POSITION_Y) == iYPos)
		//	return true;	//겹치기 테스트 기존

		if (m_ObstacleBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_ObstacleBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//겹치기 테스트-팩토리 적용
	}

	return false;
}


Position BlockManager::GetRandomPosition(int i)
{
	Position tmpPosition;

	while(1)
	{
		tmpPosition.m_iy = (rand() % (MAP_HEIGHT - 2)) + 1;
		tmpPosition.m_ix = (rand() % (MAP_WIDTH - 2)) + 1;

		if (IsOverlap(tmpPosition.m_ix, tmpPosition.m_iy, i) == false)
		{
			if (tmpPosition.m_ix != ((MAP_WIDTH / 2) + 1) && tmpPosition.m_iy != ((MAP_HEIGHT / 2) + 1))
				break;	//중복 아니라고 판정되면 해당 방해물 저장
		}
	}
	
	return tmpPosition;

	//이 함수는 고칠 필요 ㄴㄴ
}


void BlockManager::SetRandObstacle()
{
	//방해물 생성-기존
	/*if (m_Obstacle != NULL)
		delete[] m_Obstacle;
		
	m_Obstacle = new Block[MAX_OBS];
	for (int i = 0; i < MAX_OBS; i++)
	{
		m_Obstacle[i].SetBlock(BLOCK_ATTRIBUTE_OBSTACLE, GetRandomPosition(i));
		m_Obstacle[i].DrawBlock();
	}*/

	
	//방해물 생성-팩토리 적용
	if (!m_ObstacleBlockVector.empty())
		m_ObstacleBlockVector.clear();

	NewObstacleBlockFactory = new ObstacleBlockFactory();

	for (int i = 0; i < MAX_OBS; i++)
	{
		Block *NewObstacleBlock = NewObstacleBlockFactory->CreateNewBlockClass();

		NewObstacleBlock->SetBlockPosition(GetRandomPosition(i));
		m_ObstacleBlockVector.push_back(NewObstacleBlock);
		NewObstacleBlock->DrawBlock();
	}
}


void BlockManager::InitFeed()
{
	//먹이 초기화-기존
	//if (m_Feed != NULL)
	//	delete[] m_Feed;

	//m_Feed = new Block[MAX_FEED];


	//먹이 배열 초기화-팩토리 적용
	if (!m_FeedBlockVector.empty())
		m_FeedBlockVector.clear();

	NewFeedBlockFactory = new FeedBlockFactory();
	m_iCurrentFeedCount = 0;
	m_bIsCountedMaxFeed = false;
}


void BlockManager::SetRandFeed(int i)
{
	//먹이 생성-기존
	
	//int j = 0;
	//for (; j < MAX_FEED; j++)
	//{
	//	if (m_Feed[j].GetPosition(POSITION_X) <= 0)
	//		break;
	//}
	//
	//m_Feed[j].SetBlock(BLOCK_ATTRIBUTE_FEED, GetRandomPositionFeed());
	//m_Feed[j].DrawBlock();


	//먹이 생성-팩토리 적용

	if (m_FeedBlockVector.size() <= MAX_FEED)
	{
		Block *NewFeedBlock = NewFeedBlockFactory->CreateNewBlockClass();

		NewFeedBlock->SetBlockPosition(GetRandomPositionFeed());
		m_FeedBlockVector.push_back(NewFeedBlock);
		NewFeedBlock->DrawBlock();
		m_iCurrentFeedCount++;
	}
	else
	{
		int x = 0;
		for (; x < MAX_FEED; x++)
		{
			if (m_FeedBlockVector[x]->GetPosition(POSITION_X) <= 0)
				break;
		}

		m_FeedBlockVector[x]->SetBlock(BLOCK_ATTRIBUTE_FEED, GetRandomPositionFeed());
		m_FeedBlockVector[x]->DrawBlock();
	}
	
}


Position BlockManager::GetRandomPositionFeed()
{
	Position tmpPosition;

	while (1)
	{
		tmpPosition.m_iy = (rand() % (MAP_HEIGHT - 2)) + 1;
		tmpPosition.m_ix = (rand() % (MAP_WIDTH - 2)) + 1;

		if (IsOverlapFeed(tmpPosition.m_ix, tmpPosition.m_iy) == false)
		{
			if (tmpPosition.m_ix != ((MAP_WIDTH / 2) + 1) && tmpPosition.m_iy != ((MAP_HEIGHT / 2) + 1))
				break;	//중복 아니라고 판정되면 해당 먹이 저장
		}
	}

	return tmpPosition;

	//이 함수는 고칠 필요 ㄴㄴ
}


bool BlockManager::IsOverlapFeed(int iXPos, int iYPos)
{
	//먹이 중복 확인-기존
	
	//for (int x = 0; x < MAX_OBS; x++)
	//{
	//	if (m_Obstacle[x].GetPosition(POSITION_X) == iXPos && m_Obstacle[x].GetPosition(POSITION_Y) == iYPos)
	//		return true;	//방해물과 위치 겹치면 ㄴㄴ
	//}

	//for (int x = 0; x < MAX_FEED; x++)
	//{
	//	if (m_Feed[x].GetPosition(POSITION_X) == iXPos && m_Feed[x].GetPosition(POSITION_Y) == iYPos)
	//		return true;	//다른 먹이와 위치 겹치면 ㄴㄴ
	//}

	//return false;

	
	//먹이 중복 확인-팩토리 적용
	
	for (int x = 0; x < MAX_OBS; x++)
	{
		if (m_ObstacleBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_ObstacleBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//방해물과 위치 겹치면 ㄴㄴ
	}

	int x = 0;
	for (std::vector <Block*>::iterator iter = m_FeedBlockVector.begin(); iter != m_FeedBlockVector.end(); ++iter)
	{
		if (m_FeedBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_FeedBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//다른 먹이와 위치 겹치면 ㄴㄴ

		x++;
	}

	return false;
}


void BlockManager::DrawWallBlock()
{
	for (int i = 0; i < m_iWallCount; i++)
	{
		//m_BlockWall[i].DrawBlock(); //벽그리기 기존

		//신규
		m_WallBlockVector[i]->DrawBlock();
	}
}


int BlockManager::IsCollisionObject(int iSnakeX, int iSnakeY)
{
	if (iSnakeX == 0 || iSnakeX == (MAP_WIDTH - 1) || iSnakeY == 0 || iSnakeY == (MAP_HEIGHT - 1))
		return CASE_COLLISION_WALL;

	
	//충돌 확인-기존
	
	/*for (int i = 0; i < MAX_OBS; i++)
	{
		if (m_Obstacle[i].GetPosition(POSITION_X) == iSnakeX && m_Obstacle[i].GetPosition(POSITION_Y) == iSnakeY)
			return CASE_COLLISION_OBJECT;
	}

	for (int i = 0; i < MAX_FEED; i++)
	{
		if (m_Feed[i].GetPosition(POSITION_X) == iSnakeX && m_Feed[i].GetPosition(POSITION_Y) == iSnakeY)
		{
			DeleteFeed(&m_Feed[i]);
			m_Feed[i].DeletePosition();
			return CASE_FEED;
		}
	}

	return CASE_NEUTRAL;*/


	//충돌 확인-신규

	for (int i = 0; i < MAX_OBS; i++)
	{
		if (m_ObstacleBlockVector[i]->GetPosition(POSITION_X) == iSnakeX && m_ObstacleBlockVector[i]->GetPosition(POSITION_Y) == iSnakeY)
			return CASE_COLLISION_OBJECT;
	}

	int x = 0;
	for (std::vector <Block*>::iterator iter = m_FeedBlockVector.begin(); iter != m_FeedBlockVector.end(); ++iter)
	{
		if (m_FeedBlockVector[x]->GetPosition(POSITION_X) == iSnakeX && m_FeedBlockVector[x]->GetPosition(POSITION_Y) == iSnakeY)
		{
			DeleteFeed(m_FeedBlockVector[x]);
			m_FeedBlockVector[x]->DeletePosition();
			return CASE_FEED;
		}
		x++;
	}

	return CASE_NEUTRAL;
}


void BlockManager::DeleteFeed(Block *DeleteFeed)
{
	DeleteFeed = NULL;
	delete DeleteFeed;
}

void BlockManager::DeleteBlocks()
{
	int x = 0;

	for (std::vector <Block*>::iterator iter = m_FeedBlockVector.begin(); iter != m_FeedBlockVector.end(); ++iter)
	{
		delete m_FeedBlockVector[x];

		x++;
	}

	x = 0;

	for (std::vector <Block*>::iterator iter = m_ObstacleBlockVector.begin(); iter != m_ObstacleBlockVector.end(); ++iter)
	{
		delete m_ObstacleBlockVector[x];

		x++;
	}
}

void BlockManager::DeleteWallBlocks()
{
	int x = 0;

	for (std::vector <Block*>::iterator iter = m_WallBlockVector.begin(); iter != m_WallBlockVector.end(); ++iter)
	{
		delete m_WallBlockVector[x];

		x++;
	}
}

BlockManager::~BlockManager()
{
	/*delete[] m_BlockWall;
	delete[] m_Feed;
	delete[] m_Obstacle;*/

	delete NewWallBlockFactory;
	delete NewFeedBlockFactory;
	delete NewObstacleBlockFactory;

}


//3월 9일 먹이 생성 팩토리 전용으로 고치고 있었음