#include "Snake.h"

Snake::Snake()
{
	m_iLife = 1;
	Head = new SnakeInfo;
	Head->isHead = true;
	Head->iXPos = 50;
	Head->iYPos = 15;
	Head->Next = NULL;
	//대머리 생성
}


Snake::~Snake()
{
}
