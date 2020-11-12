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
	BlockCoordinate m_MyCoordinate;	//�� ��ǥ
	BLOCK_ATTRIBUTE m_MyAttribute;	//�� �Ӽ�
	std::string m_sMyShape;			//�� ���

public:
	Block();
	void SetBlock(BlockCoordinate TemporaryCoordinate, BLOCK_ATTRIBUTE TemporaryAttribute);
	void DrawBlock();


	~Block();
};

