#pragma once
#include "Headers.h"

//�� �Ӽ�
enum BLOCK_ATTRIBUTE
{
	BLOCK_ATTRIBUTE_WALL,
	BLOCK_ATTRIBUTE_BREAKABLE,
	BLOCK_ATTRIBUTE_BROKEN,
	BLOCK_ATTRIBUTE_LAVA,
	BLOCK_ATTRIBUTE_BRIDGE,
	BLOCK_ATTRIBUTE_SWITCH,
	BLOCK_ATTRIBUTE_DOOR,
	BLOCK_ATTRIBUTE_START,
	BLOCK_ATTRIBUTE_END,
	BLOCK_ATTRIBUTE_USER,
	BLOCK_ATTRIBUTE_USER_DEAD
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Position
{
	int m_iXcoordinate;
	int m_iYcoordinate;
}BlockCoordinate;


class Block
{
private:
	BlockCoordinate m_MyCoordinate;	//�� ��ǥ
	BLOCK_ATTRIBUTE m_MyAttribute;	//�� �Ӽ�
	std::string m_sMyShape;			//�� ���

public:
	Block();
	void SetBlock(BlockCoordinate TemporaryCoordinate, BLOCK_ATTRIBUTE TemporaryAttribute);
	void DrawBlock();


	~Block();
};

