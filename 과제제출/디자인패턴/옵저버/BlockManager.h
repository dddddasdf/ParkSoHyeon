#pragma once
#include "Block.h"
#include "BlockFactory.h"

class BlockManager
{
private:
	/*Block* m_BlockWall;
	Block* m_BlockObjects;
	Block* m_BlockPlayer;*/
	std::vector <std::vector <int>> m_vBlockVector;
public:
	BlockManager();
	void SetBlocks();	//벽 좌표를 담을 벡터 생성
	void PrintBlocks();	//블럭들 출력
	~BlockManager();
};

