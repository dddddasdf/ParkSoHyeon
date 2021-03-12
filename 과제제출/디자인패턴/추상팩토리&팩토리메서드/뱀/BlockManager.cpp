#include "BlockManager.h"

#define NOT_EXSIT_FEED -10

BlockManager::BlockManager()
{
	NewWallBlockFactory = new WallBlockFactory();
	

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

	//�� �Լ��� ��ĥ �ʿ� ����
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
	//���� �ʱ�ȭ-����
	//if (m_Feed != NULL)
	//	delete[] m_Feed;

	//m_Feed = new Block[MAX_FEED];


	//���� �迭 �ʱ�ȭ-���丮 ����
	if (!m_FeedBlockVector.empty())
		m_FeedBlockVector.clear();

	NewFeedBlockFactory = new FeedBlockFactory();
	m_iCurrentFeedCount = 0;
	m_bIsCountedMaxFeed = false;
}


void BlockManager::SetRandFeed(int i)
{
	//���� ����-����
	
	//int j = 0;
	//for (; j < MAX_FEED; j++)
	//{
	//	if (m_Feed[j].GetPosition(POSITION_X) <= 0)
	//		break;
	//}
	//
	//m_Feed[j].SetBlock(BLOCK_ATTRIBUTE_FEED, GetRandomPositionFeed());
	//m_Feed[j].DrawBlock();


	//���� ����-���丮 ����

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
				break;	//�ߺ� �ƴ϶�� �����Ǹ� �ش� ���� ����
		}
	}

	return tmpPosition;

	//�� �Լ��� ��ĥ �ʿ� ����
}


bool BlockManager::IsOverlapFeed(int iXPos, int iYPos)
{
	//���� �ߺ� Ȯ��-����
	
	//for (int x = 0; x < MAX_OBS; x++)
	//{
	//	if (m_Obstacle[x].GetPosition(POSITION_X) == iXPos && m_Obstacle[x].GetPosition(POSITION_Y) == iYPos)
	//		return true;	//���ع��� ��ġ ��ġ�� ����
	//}

	//for (int x = 0; x < MAX_FEED; x++)
	//{
	//	if (m_Feed[x].GetPosition(POSITION_X) == iXPos && m_Feed[x].GetPosition(POSITION_Y) == iYPos)
	//		return true;	//�ٸ� ���̿� ��ġ ��ġ�� ����
	//}

	//return false;

	
	//���� �ߺ� Ȯ��-���丮 ����
	
	for (int x = 0; x < MAX_OBS; x++)
	{
		if (m_ObstacleBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_ObstacleBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//���ع��� ��ġ ��ġ�� ����
	}

	int x = 0;
	for (std::vector <Block*>::iterator iter = m_FeedBlockVector.begin(); iter != m_FeedBlockVector.end(); ++iter)
	{
		if (m_FeedBlockVector[x]->GetPosition(POSITION_X) == iXPos && m_FeedBlockVector[x]->GetPosition(POSITION_Y) == iYPos)
			return true;	//�ٸ� ���̿� ��ġ ��ġ�� ����

		x++;
	}

	return false;
}


void BlockManager::DrawWallBlock()
{
	for (int i = 0; i < m_iWallCount; i++)
	{
		//m_BlockWall[i].DrawBlock(); //���׸��� ����

		//�ű�
		m_WallBlockVector[i]->DrawBlock();
	}
}


int BlockManager::IsCollisionObject(int iSnakeX, int iSnakeY)
{
	if (iSnakeX == 0 || iSnakeX == (MAP_WIDTH - 1) || iSnakeY == 0 || iSnakeY == (MAP_HEIGHT - 1))
		return CASE_COLLISION_WALL;

	
	//�浹 Ȯ��-����
	
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


	//�浹 Ȯ��-�ű�

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


//3�� 9�� ���� ���� ���丮 �������� ��ġ�� �־���