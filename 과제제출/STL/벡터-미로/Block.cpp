#include "Block.h"

Block::Block()
{

}

void Block::SetBlock(BlockCoordinate TemporaryCoordinate, BLOCK_ATTRIBUTE TemporaryAttribute)
{
	m_MyAttribute = TemporaryAttribute;

	switch (m_MyAttribute)
	{
	case BLOCK_ATTRIBUTE_WALL:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_BREAKABLE:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_BROKEN:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_LAVA:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_BRIDGE:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_DOOR:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_SWITCH:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_START:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_END:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_USER:
		m_sMyShape = "��";
		break;
	case BLOCK_ATTRIBUTE_USER_DEAD:
		m_sMyShape = "��";
		break;
	}

	m_MyCoordinate = TemporaryCoordinate;
}

void Block::DrawBlock()
{
	gotoxy(m_MyCoordinate.m_iXcoordinate * 2, m_MyCoordinate.m_iYcoordinate);
	std::cout << m_sMyShape;
}


Block::~Block()
{

}