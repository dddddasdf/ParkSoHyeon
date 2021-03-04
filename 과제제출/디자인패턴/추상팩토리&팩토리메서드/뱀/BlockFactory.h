#pragma once
#include <vector>
#include "Block.h"

//블락매니저랑 얘랑 하는 일 차이가??
//둘을 어케 분리하지

//factory는 만들고 manage는 출력만?? 맞나 이게

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