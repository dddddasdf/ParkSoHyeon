#include "BlockFactory.h"

BlockFactory::~BlockFactory()
{
	Blocks.clear();
}

void BlockFactory::AddBlock(Block *NewBlock)
{
	Blocks.push_back(NewBlock);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////벽

Block* WallBlockFactory::CreateNewBlockClass(Position P)
{
	/*Block *NewWallBlock = new Block;

	NewWallBlock->SetBlock(BLOCK_ATTRIBUTE_WALL, P);

	return NewWallBlock;*/

	return new WallBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////먹이

Block* FeedBlockFactory::CreateNewBlockClass(Position P)
{
	/*Block *NewFeedBlock = new Block;

	NewFeedBlock->SetBlock(BLOCK_ATTRIBUTE_FEED, P);

	return NewFeedBlock;*/

	return new FeedBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////방해물

Block* ObstacletBlockFactory::CreateNewBlockClass(Position P)
{
	/*Block *NewObstacleBlock = new Block;

	NewObstacleBlock->SetBlock(BLOCK_ATTRIBUTE_OBSTACLE, P);

	return NewObstacleBlock;*/

	return new ObstacleBlock;
}