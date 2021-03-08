#pragma once
#include "headers.h"
#include "Headers (2).h"

struct Position
{
	int m_ix;
	int m_iy;
};

class Block
{
private:
	BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;
public:
	Block();
	void SetBlock(BLOCK_ATTRIBUTE Attribute, Position P);
	void DrawBlock();
	void DeleteBlock(int x, int y);
	int GetPosition(int Pos);
	void DeletePosition();

	~Block();
};

class WallBlock : public Block
{
private:
	BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;
public:
	WallBlock();

};

class FeedBlock : public Block
{
private:
	BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;
public:
	FeedBlock();

};

class ObstacleBlock : public Block
{
private:
	BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;
public:
	ObstacleBlock();

};