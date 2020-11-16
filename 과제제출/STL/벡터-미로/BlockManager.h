#pragma once
#include "Block.h"

class BlockManager
{
private:
	Block* m_BlockWall;
	Block* m_BlockObjects;
	Block* m_BlockPlayer;
public:
	BlockManager();
	BlockCoordinate SetBlocks();	//벽 좌표를 담을 벡터 생성
	~BlockManager();
};

