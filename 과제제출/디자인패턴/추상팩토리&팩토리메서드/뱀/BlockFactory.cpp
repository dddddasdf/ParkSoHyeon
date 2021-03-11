#include "BlockFactory.h"

BlockFactory::~BlockFactory()
{
	Blocks.clear();
}

void BlockFactory::AddBlock(Block *NewBlock)
{
	Blocks.push_back(NewBlock);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////��

Block* WallBlockFactory::CreateNewBlockClass()
{
	return new WallBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////����

Block* FeedBlockFactory::CreateNewBlockClass()
{
	return new FeedBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////���ع�

Block* ObstacleBlockFactory::CreateNewBlockClass()
{
	return new ObstacleBlock;
}