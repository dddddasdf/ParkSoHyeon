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
	void SetBlocks();	//�� ��ǥ�� ���� ���� ����
	void PrintBlocks();	//���� ���
	~BlockManager();
};

