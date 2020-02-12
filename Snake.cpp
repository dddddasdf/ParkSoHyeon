#include "Snake.h"

Snake::Snake()
{
	Position HeadPosition;
	m_iLife = 1;
	Head = new SnakeInfo;
	Head->isHead = true;
	HeadPosition.m_ix = (MAP_WIDTH / 2) + 1;
	HeadPosition.m_iy = (MAP_HEIGHT / 2) + 1;
	Head->Next = NULL;
	Head->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_HEAD, HeadPosition);
	//대머리 생성
}

void Snake::PrintSnake()
{
	Head->Block_Snake.DrawBlock();

	Position Bodytmp;

	if (Head->Next != NULL)
	{
		tmp = Head->Next;

		while (tmp->Next != NULL)
		{
			Bodytmp.m_ix = tmp->iXPos;
			Bodytmp.m_iy = tmp->iYPos;
			tmp->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_TAIL, Bodytmp);
			tmp = tmp->Next;
		}
	}
}

void Snake::CreateBody()
{
	if (Head->Next == NULL)
	{
		Body = new SnakeInfo;
		if (m_iDirectionState == DIRECTION_RIGHT)
		{
			Body->iXPos = Head->iXPos - 2;
			Body->iYPos = Head->iYPos;
		}
		else if(m_iDirectionState == DIRECTION_LEFT)
		{
			Body->iXPos = Head->iXPos + 2;
			Body->iYPos = Head->iYPos;
		}
		else if (m_iDirectionState == DIRECTION_UP)
		{
			Body->iXPos = Head->iXPos;
			Body->iYPos = Head->iYPos - 1;
		}
		else if (m_iDirectionState == DIRECTION_DOWN)
		{
			Body->iXPos = Head->iXPos;
			Body->iYPos = Head->iYPos + 1;
		}
		Body->isHead = false;
		Head->Next = Body;
		Body->Next = NULL;
	}
	else
	{
		tmp = Head;
		while (tmp->Next != NULL)
		{
			tmp = tmp->Next;
		}

		Body = new SnakeInfo;

		if (m_iDirectionState == DIRECTION_RIGHT)
		{
			Body->iXPos = tmp->iXPos - 2;
			Body->iYPos = tmp->iYPos;
		}
		else if (m_iDirectionState == DIRECTION_LEFT)
		{
			Body->iXPos = tmp->iXPos + 2;
			Body->iYPos = tmp->iYPos;
		}
		else if (m_iDirectionState == DIRECTION_UP)
		{
			Body->iXPos = tmp->iXPos;
			Body->iYPos = tmp->iYPos - 1;
		}
		else if (m_iDirectionState == DIRECTION_DOWN)
		{
			Body->iXPos = tmp->iXPos;
			Body->iYPos = tmp->iYPos + 1;
		}
		Body->isHead = false;
		Body->Next = NULL;
		tmp->Next = Body;
	}
}

void Snake::MoveSnake()
{
	if (m_iDirectionState == DIRECTION_RIGHT)
	{
		Head->iXPos += 2;
	}
	else if (m_iDirectionState == DIRECTION_LEFT)
	{
		Head->iXPos -= 2;;
	}
	else if (m_iDirectionState == DIRECTION_UP)
	{
		Head->iYPos += 1;
	}
	else if (m_iDirectionState == DIRECTION_DOWN)
	{
		Head->iYPos -= 1;
	}

	if (Head->Next != NULL)
		MoveBody(Head);
}

void Snake::MoveBody(SnakeInfo *tmp)
{
	while (tmp->Next != NULL)
	{
		tmp->Next->iXPos = tmp->iXPos;
		tmp->Next->iYPos = tmp->iYPos;
	}
}


Snake::~Snake()
{
}
