#include "BlockManager.h"

#define NOT_EXSIT_FEED -10

BlockManager::BlockManager()
{
	NewWallBlockFactory = new WallBlockFactory();
	

	//混 持失-奄糎
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

	//混 持失-苫塘軒 旋遂
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
		//	return true;	//違帖奄 砺什闘 奄糎

		if (m_ObstacleBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_ObstacleBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//違帖奄 砺什闘-苫塘軒 旋遂
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
				break;	//掻差 焼艦虞壱 毒舛鞠檎 背雁 号背弘 煽舌
		}
	}
	
	return tmpPosition;

	//戚 敗呪澗 壱張 琶推 いい
}


void BlockManager::SetRandObstacle()
{
	//号背弘 持失-奄糎
	/*if (m_Obstacle != NULL)
		delete[] m_Obstacle;
		
	m_Obstacle = new Block[MAX_OBS];
	for (int i = 0; i < MAX_OBS; i++)
	{
		m_Obstacle[i].SetBlock(BLOCK_ATTRIBUTE_OBSTACLE, GetRandomPosition(i));
		m_Obstacle[i].DrawBlock();
	}*/

	
	//号背弘 持失-苫塘軒 旋遂
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
	//股戚 段奄鉢-奄糎
	//if (m_Feed != NULL)
	//	delete[] m_Feed;

	//m_Feed = new Block[MAX_FEED];


	//股戚 壕伸 段奄鉢-苫塘軒 旋遂
	if (!m_FeedBlockVector.empty())
		m_FeedBlockVector.clear();

	NewFeedBlockFactory = new FeedBlockFactory();
	m_iCurrentFeedCount = 0;
	m_bIsCountedMaxFeed = false;
}


void BlockManager::SetRandFeed(int i)
{
	//股戚 持失-奄糎
	
	//int j = 0;
	//for (; j < MAX_FEED; j++)
	//{
	//	if (m_Feed[j].GetPosition(POSITION_X) <= 0)
	//		break;
	//}
	//
	//m_Feed[j].SetBlock(BLOCK_ATTRIBUTE_FEED, GetRandomPositionFeed());
	//m_Feed[j].DrawBlock();


	//股戚 持失-苫塘軒 旋遂

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
				break;	//掻差 焼艦虞壱 毒舛鞠檎 背雁 股戚 煽舌
		}
	}

	return tmpPosition;

	//戚 敗呪澗 壱張 琶推 いい
}


bool BlockManager::IsOverlapFeed(int iXPos, int iYPos)
{
	//股戚 掻差 溌昔-奄糎
	
	//for (int x = 0; x < MAX_OBS; x++)
	//{
	//	if (m_Obstacle[x].GetPosition(POSITION_X) == iXPos && m_Obstacle[x].GetPosition(POSITION_Y) == iYPos)
	//		return true;	//号背弘引 是帖 違帖檎 いい
	//}

	//for (int x = 0; x < MAX_FEED; x++)
	//{
	//	if (m_Feed[x].GetPosition(POSITION_X) == iXPos && m_Feed[x].GetPosition(POSITION_Y) == iYPos)
	//		return true;	//陥献 股戚人 是帖 違帖檎 いい
	//}

	//return false;

	
	//股戚 掻差 溌昔-苫塘軒 旋遂
	
	for (int x = 0; x < MAX_OBS; x++)
	{
		if (m_ObstacleBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_ObstacleBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//号背弘引 是帖 違帖檎 いい
	}

	int x = 0;
	for (std::vector <Block*>::iterator iter = m_FeedBlockVector.begin(); iter != m_FeedBlockVector.end(); ++iter)
	{
		if (m_FeedBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_FeedBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//陥献 股戚人 是帖 違帖檎 いい

		x++;
	}

	return false;
}


void BlockManager::DrawWallBlock()
{
	for (int i = 0; i < m_iWallCount; i++)
	{
		//m_BlockWall[i].DrawBlock(); //混益軒奄 奄糎

		//重鋭
		m_WallBlockVector[i]->DrawBlock();
	}
}


int BlockManager::IsCollisionObject(int iSnakeX, int iSnakeY)
{
	if (iSnakeX == 0 || iSnakeX == (MAP_WIDTH - 1) || iSnakeY == 0 || iSnakeY == (MAP_HEIGHT - 1))
		return CASE_COLLISION_WALL;

	
	//中宜 溌昔-奄糎
	
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


	//中宜 溌昔-重鋭

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


//3杉 9析 股戚 持失 苫塘軒 穿遂生稽 壱帖壱 赤醸製