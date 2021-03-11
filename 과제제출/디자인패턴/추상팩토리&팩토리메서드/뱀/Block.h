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
	

protected:
	BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;

public:
	Block();
	void SetBlock(BLOCK_ATTRIBUTE Attribute, Position P);
	void SetBlockPosition(Position P);	//factory와 아래 자식 클래스들이 자동으로 모양 결정내버리므로 위치만 갱신해주면 된다
	void DrawBlock();
	void DeleteBlock(int x, int y);
	int GetPosition(int Pos);
	void DeletePosition();

	~Block();
};

class WallBlock : public Block
{
private:
	/*BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;*/
public:
	WallBlock();

};

class FeedBlock : public Block
{
private:
	/*BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;*/
public:
	FeedBlock();

};

class ObstacleBlock : public Block
{
private:
	/*BLOCK_ATTRIBUTE m_eAttribute;
	std::string m_strShape;
	Position m_MyPosition;*/
public:
	ObstacleBlock();

};