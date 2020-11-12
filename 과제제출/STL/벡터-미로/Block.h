#pragma once
#include "Headers.h"


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

