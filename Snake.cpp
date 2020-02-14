#include "Snake.h"

Snake::Snake()
{
	m_iLife = 1;
	Head = new SnakeInfo;
	Head->iXPos = (MAP_WIDTH / 2) + 1;
	Head->iYPos = (MAP_HEIGHT / 2) + 1;
	HeadPosition.m_ix = Head->iXPos;
	HeadPosition.m_iy = Head->iYPos;
	Head->Next = NULL;
	Head->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_HEAD, HeadPosition);
	//대머리 생성
}

void Snake::PrintSnake()
{
	HeadPosition.m_ix = Head->iXPos;
	HeadPosition.m_iy = Head->iYPos;
	Head->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_HEAD, HeadPosition);
	Head->Block_Snake.DrawBlock();

	tmp = Head;

	if (Head->Next != NULL)
	{
		tmp = Head->Next;

		while (tmp->Next != NULL)
		{
			Bodytmp.m_ix = tmp->iXPos;
			Bodytmp.m_iy = tmp->iYPos;
			tmp->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_TAIL, Bodytmp);
			tmp->Block_Snake.DrawBlock();
			DeleteAfterimage(tmp);
			tmp = tmp->Next;
		}
	}

	DeleteAfterimage(Head);	//잔상 제거
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
		Body->Next = NULL;
		tmp->Next = Body;
	}
}

void Snake::MoveSnake()
{
	if (m_iDirectionState == DIRECTION_NEUTRAL)
		return;
	
	if (m_iDirectionState == DIRECTION_RIGHT)
	{
		Head->iXPos += 1;
	}
	else if (m_iDirectionState == DIRECTION_LEFT)
	{
		Head->iXPos -= 1;
	}
	else if (m_iDirectionState == DIRECTION_UP)
	{
		Head->iYPos -= 1;
	}
	else if (m_iDirectionState == DIRECTION_DOWN)
	{
		Head->iYPos += 1;
	}

	if (Head->Next != NULL)
		MoveBody(Head);
}

void Snake::MoveBody(SnakeInfo *tmp2)
{
	while (tmp2->Next != NULL)
	{
		tmp2->Next->iXPos = tmp2->iXPos;
		tmp2->Next->iYPos = tmp2->iYPos;
		tmp2 = tmp2->Next;
	}
}

void Snake::ChangeDirection(int iDirection)
{
	if (m_iDirectionState == DIRECTION_LEFT)
	{
		if (iDirection == DIRECTION_RIGHT)
			return;
	}
	else if (m_iDirectionState == DIRECTION_RIGHT)
	{
		if (iDirection == DIRECTION_LEFT)
			return;
	}
	else if (m_iDirectionState == DIRECTION_UP)
	{
		if (iDirection == DIRECTION_DOWN)
			return;
	}
	else if (m_iDirectionState == DIRECTION_DOWN)
	{
		if (iDirection == DIRECTION_UP)
			return;
	}
	//위에는 지금 가는 방향 반대로 방향 돌리지 못하게 막는 조건식들

	m_iDirectionState = iDirection;
}

void Snake::DeleteAfterimage(SnakeInfo *tmp2)
{
	if (m_iDirectionState == DIRECTION_RIGHT)
	{
		gotoxy(((tmp2->iXPos) * 2) - 2, (tmp2->iYPos));
		std::cout << "  ";
	}
	else if (m_iDirectionState == DIRECTION_LEFT)
	{
		gotoxy(((tmp2->iXPos) * 2) + 2, (tmp2->iYPos));
		std::cout << "  ";
	}
	else if (m_iDirectionState == DIRECTION_UP)
	{
		gotoxy(((tmp2->iXPos) * 2), (tmp2->iYPos) + 1);
		std::cout << "  ";
	}
	else if (m_iDirectionState == DIRECTION_DOWN)
	{
		gotoxy(((tmp2->iXPos) * 2), (tmp2->iYPos) - 1);
		std::cout << "  ";
	}
}

void Snake::GetSnakePosition(int *iSnakeX, int *iSnakeY)
{
	*iSnakeX = Head->iXPos;
	*iSnakeY = Head->iYPos;
}

Snake::~Snake()
{
}
