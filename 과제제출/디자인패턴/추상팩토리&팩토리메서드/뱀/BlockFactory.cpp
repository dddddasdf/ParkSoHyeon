#include "BlockFactory.h"

BlockFactory::~BlockFactory()
{
	Blocks.clear();
}

void BlockFactory::AddBlock(Block *NewBlock)
{
	Blocks.push_back(NewBlock);
}

