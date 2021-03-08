#include "Block.h"



Block::Block()
{
}


void Block::SetBlock(BLOCK_ATTRIBUTE Attribute, Position P)
{
	m_eAttribute = Attribute;
	switch (m_eAttribute)
	{
	case BLOCK_ATTRIBUTE_WALL:
		m_strShape = "▩";
		break;
	case BLOCK_ATTRIBUTE_OBSTACLE:
		m_strShape = "■";
		break;
	case BLOCK_ATTRIBUTE_HEAD:
		m_strShape = "●";
		break;
	case BLOCK_ATTRIBUTE_TAIL:
		m_strShape = "○";
		break;
	case BLOCK_ATTRIBUTE_FEED:
		m_strShape = "☆";
		break;
	case BLOCK_ATTRIBUTE_NONE:
		m_strShape = " ";
		break;
	}
	m_MyPosition = P;
}

void Block::DrawBlock()
{
	gotoxy(m_MyPosition.m_ix * 2, m_MyPosition.m_iy);
	std::cout << m_strShape;
}

int Block::GetPosition(int Pos)
{
	if (Pos == POSITION_X)
		return m_MyPosition.m_ix;
	else if (Pos == POSITION_Y)
		return m_MyPosition.m_iy;
}

void Block::DeleteBlock(int x, int y)
{
	gotoxy(x, y);
	std::cout << "　";
}

void Block::DeletePosition()
{
	m_MyPosition.m_ix = NULL;
	m_MyPosition.m_iy = NULL;
}

Block::~Block()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////벽

WallBlock::WallBlock()
{
	m_eAttribute = BLOCK_ATTRIBUTE_WALL;
	m_strShape = "▩";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////먹이

FeedBlock::FeedBlock()
{
	m_eAttribute = BLOCK_ATTRIBUTE_FEED;
	m_strShape = "☆";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////방해물

ObstacleBlock::ObstacleBlock()
{
	m_eAttribute = BLOCK_ATTRIBUTE_OBSTACLE;
	m_strShape = "■";
}