#include "BlockManager.h"



BlockManager::BlockManager()
{
	NewWallBlockFactory = new WallBlockFactory();
	NewFeedBlockFacotory = new FeedBlockFactory();
	NewObstacletBlockFactory = new ObstacletBlockFactory();

	//�� ����-����
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

	//�� ����-���丮 ����
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
		//	return true;	//��ġ�� �׽�Ʈ ����

		if (m_ObstacleBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_ObstacleBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//��ġ�� �׽�Ʈ-���丮 ����
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
				break;	//�ߺ� �ƴ϶�� �����Ǹ� �ش� ���ع� ����
		}
	}
	
	return tmpPosition;
}


void BlockManager::SetRandObstacle()
{
	//���ع� ����-����
	/*if (m_Obstacle != NULL)
		delete[] m_Obstacle;
		
	m_Obstacle = new Block[MAX_OBS];
	for (int i = 0; i < MAX_OBS; i++)
	{
		m_Obstacle[i].SetBlock(BLOCK_ATTRIBUTE_OBSTACLE, GetRandomPosition(i));
		m_Obstacle[i].DrawBlock();
	}*/

	
	//���ع� ����-���丮 ����
	if (!m_ObstacleBlockVector.empty())
		m_ObstacleBlockVector.clear();

	for (int i = 0; i < MAX_OBS; i++)
	{
		Block *NewObstacleBlock = NewObstacletBlockFactory->CreateNewBlockClass();
		NewObstacleBlock->SetBlockPosition(GetRandomPosition(i));
		m_ObstacleBlockVector.push_back(NewObstacleBlock);
		NewObstacleBlock->DrawBlock();
	}
}


void BlockManager::InitFeed()
{
	//���� �ʱ�ȭ-����
	//if (m_Feed != NULL)
	//	delete[] m_Feed;

	//m_Feed = new Block[MAX_FEED];


	//���� �ʱ�ȭ-���丮 ����
	if (!m_FeedBlockVector.empty())
		m_FeedBlockVector.clear();

}


void BlockManager::SetRandFeed(int i)
{
	//���� ����-����
	
	int j = 0;
	for (; j < MAX_FEED; j++)
	{
		if (m_Feed[j].GetPosition(POSITION_X) <= 0)
			break;
	}
	
	m_Feed[j].SetBlock(BLOCK_ATTRIBUTE_FEED, GetRandomPositionFeed());
	m_Feed[j].DrawBlock();


	//���� ����-���丮 ����

	int x = 0;
	for (; x < MAX_FEED; x++)
	{
		if (m_Feed[x].GetPosition(POSITION_X) <= 0)
			break;
	}

	m_Feed[x].SetBlock(BLOCK_ATTRIBUTE_FEED, GetRandomPositionFeed());
	m_Feed[x].DrawBlock();
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
				break;	//�ߺ� �ƴ϶�� �����Ǹ� �ش� ���ع� ����
		}
	}

	return tmpPosition;
}


bool BlockManager::IsOverlapFeed(int iXPos, int iYPos)
{
	for (int x = 0; x < MAX_OBS; x++)
	{
		if (m_Obstacle[x].GetPosition(POSITION_X) == iXPos && m_Obstacle[x].GetPosition(POSITION_Y) == iYPos)
			return true;	//���ع��� ��ġ ��ġ�� ����
	}

	for (int x = 0; x < MAX_FEED; x++)
	{
		if (m_Feed[x].GetPosition(POSITION_X) == iXPos && m_Feed[x].GetPosition(POSITION_Y) == iYPos)
			return true;	//�ٸ� ���̿� ��ġ ��ġ�� ����
	}

	return false;
}


void BlockManager::DrawWallBlock()
{
	for (int i = 0; i < m_iWallCount; i++)
	{
		//m_BlockWall[i].DrawBlock(); //���׸��� ����
		m_WallBlockVector[i]->DrawBlock();
	}
}


int BlockManager::IsCollisionObject(int iSnakeX, int iSnakeY)
{
	if (iSnakeX == 0 || iSnakeX == (MAP_WIDTH - 1) || iSnakeY == 0 || iSnakeY == (MAP_HEIGHT - 1))
		return CASE_COLLISION_WALL;

	for (int i = 0; i < MAX_OBS; i++)
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

	return CASE_NEUTRAL;
}


void BlockManager::DeleteFeed(Block *DeleteFeed)
{
	DeleteFeed = NULL;
	delete DeleteFeed;
}


BlockManager::~BlockManager()
{
	delete[] m_BlockWall;
	delete[] m_Feed;
	delete[] m_Obstacle;
}


//3�� 9�� ���� ���� ���丮 �������� ��ġ�� �־���