#include "Snake.h"

Snake::Snake()
{
	m_iLife = 1;
	Head = new SnakeInfo;
	Head->isHead = true;
	Head->iXPos = 50;
	Head->iYPos = 15;
	Head->Next = NULL;
	//��Ӹ� ����
}


Snake::~Snake()
{
}
