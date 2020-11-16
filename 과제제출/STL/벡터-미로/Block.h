#pragma once
#include "Headers.h"

//블럭 속성
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
	BlockCoordinate m_MyCoordinate;	//블럭 좌표
	BLOCK_ATTRIBUTE m_MyAttribute;	//블럭 속성
	std::string m_sMyShape;			//블럭 모양

public:
	Block();
	void SetBlock(BlockCoordinate TemporaryCoordinate, BLOCK_ATTRIBUTE TemporaryAttribute);
	void DrawBlock();


	~Block();
};

