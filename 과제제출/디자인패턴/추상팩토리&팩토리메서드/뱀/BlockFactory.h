#pragma once
#include <vector>
#include "Block.h"

//����Ŵ����� ��� �ϴ� �� ���̰�??
//���� ���� �и�����

//factory�� ����� manage�� ��¸�?? �³� �̰�

class BlockFactory
{
private:
	std::vector <Block*> Blocks;

protected:
	void AddBlock(Block* NewBlock);

public:
	~BlockFactory();

	virtual Block* CreateNewBlock() = 0;
};

class WallBlock : public BlockFactory
{
	
};

class FeedBlock : public BlockFactory
{

};

class ObstacletBlock : public BlockFactory
{

};