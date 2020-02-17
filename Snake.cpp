#include "Snake.h"

Snake::Snake()
{
}

void Snake::PrintSnake()
{
	if (Head->Next == NULL)
		DeleteAfterimage(HeadPosition.m_ix, HeadPosition.m_iy);	//잔상 제거
	HeadPosition.m_ix = Head->iXPos;
	HeadPosition.m_iy = Head->iYPos;
	Head->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_HEAD, HeadPosition);
	Head->Block_Snake.DrawBlock();

	tmp = Head;

	if (Head->Next != NULL)
	{
		tmp = Head->Next;

		while (1)
		{
			/*if (tmp->Next == NULL)
				DeleteAfterimage(Bodytmp.m_ix, Bodytmp.m_iy);*/
			Bodytmp.m_ix = tmp->iXPos;
			Bodytmp.m_iy = tmp->iYPos;
			tmp->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_TAIL, Bodytmp);
			tmp->Block_Snake.DrawBlock();
			
			if (tmp->Next == NULL)
				break;

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
	Bodytmp.m_ix = tmp->iXPos;
	Bodytmp.m_iy = tmp->iYPos;
}

void Snake::MoveSnake()
{
	if (m_iDirectionState == DIRECTION_NEUTRAL)
		return;
	
	if (m_iDirectionState == DIRECTION_RIGHT)
	{
		if (Head->Next != NULL)
			MoveBody(Head);
		Head->iXPos += 1;
	}
	else if (m_iDirectionState == DIRECTION_LEFT)
	{
		if (Head->Next != NULL)
			MoveBody(Head);
		Head->iXPos -= 1;
	}
	else if (m_iDirectionState == DIRECTION_UP)
	{
		if (Head->Next != NULL)
			MoveBody(Head);
		Head->iYPos -= 1;
	}
	else if (m_iDirectionState == DIRECTION_DOWN)
	{
		if (Head->Next != NULL)
			MoveBody(Head);
		Head->iYPos += 1;
	}
}

void Snake::MoveBody(SnakeInfo *tmp2)
{
	int x, y;

	while (1)
	{
		x = tmp2->Next->iXPos;
		y = tmp2->Next->iYPos;
		tmp2->Next->iXPos = tmp2->iXPos;
		tmp2->Next->iYPos = tmp2->iYPos;

		if (tmp2->Next->Next == NULL)
			break;

		tmp2 = tmp2->Next;
	}
	DeleteAfterimage(x, y);
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

void Snake::DeleteAfterimage(int x, int y)
{
	gotoxy((x * 2), y);
	std::cout << "  ";
}

void Snake::GetSnakePosition(int *iSnakeX, int *iSnakeY)
{
	*iSnakeX = Head->iXPos;
	*iSnakeY = Head->iYPos;
}

void Snake::InitSnakePosition()
{
	Head = new SnakeInfo;
	tmp = new SnakeInfo;
	Head->iXPos = (MAP_WIDTH / 2) + 1;
	Head->iYPos = (MAP_HEIGHT / 2) + 1;
	HeadPosition.m_ix = Head->iXPos;
	HeadPosition.m_iy = Head->iYPos;
	Head->Next = NULL;
	Head->Block_Snake.SetBlock(BLOCK_ATTRIBUTE_HEAD, HeadPosition);
}

void Snake::KillSnake()
{
	if (Head->Next != NULL)
	{
		SnakeInfo *tmp2;
		tmp = Head->Next;
		
		while (tmp->Next != NULL)
		{
			tmp2 = tmp->Next;
			tmp->iXPos = NULL;
			tmp->iYPos = NULL;
			Bodytmp.m_ix = tmp->iXPos;
			Bodytmp.m_iy = tmp->iYPos;
			tmp = tmp2;
		}

		tmp2 = tmp;
	}
		
	Head->iXPos = NULL;
	Head->iYPos = NULL;
	HeadPosition.m_ix = Head->iXPos;
	HeadPosition.m_iy = Head->iYPos;

	delete Head;
	//delete tmp;
}

Snake::~Snake()
{
}
