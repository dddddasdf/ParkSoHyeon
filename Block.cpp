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
		m_strShape = "��";
		break;
	case BLOCK_ATTRIBUTE_OBS:
		m_strShape = "��";
		break;
	case BLOCK_ATTRIBUTE_HEAD:
		m_strShape = "��";
		break;
	case BLOCK_ATTRIBUTE_TAIL:
		m_strShape = "��";
		break;
	case BLOCK_ATTRIBUTE_FEED:
		m_strShape = "��";
		break;
	}
	if (m_eAttribute == BLOCK_ATTRIBUTE_FEED)
		m_bLiveStatus = false;
	else
		m_bLiveStatus = true;
	m_MyPosition = P;
}

void Block::DrawBlock()
{
	gotoxy(m_MyPosition.m_ix * 2, m_MyPosition.m_iy);
	std::cout << m_strShape;
}

int Block::GetPosition(int Pos)
{
	if (Pos == 1)
		return m_ix;
	else if (Pos == 2)
		return m_iy;
}

Block::~Block()
{
}
