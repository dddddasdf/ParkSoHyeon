#include "BlockManager.h"



BlockManager::BlockManager()
{
	m_iWallCount = ((MAP_WIDTH * 2) + (MAP_HEIGHT * 2)) - 4;
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
	}
	m_Obstacle = NULL;
	m_Feed = NULL;
}

bool BlockManager::IsOverlap(int iXPos, int iYPos, int i)
{
	for (int x = 0; x < i; x++)
	{
		if (m_Obstacle[x].GetPosition(POSITION_X) == iXPos && m_Obstacle[x].GetPosition(POSITION_Y) == iYPos)
			return true;
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
}


void BlockManager::SetRandObstacle()
{
	if (m_Obstacle != NULL)
		delete[] m_Obstacle;
		
	m_Obstacle = new Block[MAX_OBS];
	for (int i = 0; i < MAX_OBS; i++)
	{
		m_Obstacle[i].SetBlock(BLOCK_ATTRIBUTE_OBS, GetRandomPosition(i));
		m_Obstacle[i].DrawBlock();
	}
}

void BlockManager::InitFeed()
{
	m_iFeedCount = 0;


}

void BlockManager::DrawWallBlock()
{
	for (int i = 0; i < m_iWallCount; i++)
	{
		m_BlockWall[i].DrawBlock();
	}
}


BlockManager::~BlockManager()
{
	delete[] m_BlockWall;
}
