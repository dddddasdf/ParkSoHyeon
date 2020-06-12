#include "Queue.h"

void InitLine(Line *LinePoint)
{
	LinePoint->Front = NULL;
	LinePoint->Rear = NULL;
	LinePoint->iWaitingPeople = 0;
}

void AddNode(Line *LinePoint, int Code)
{
	User *NewNode = new User;
	NewNode->iIdentifyCode = Code;
	NewNode->Next = NULL;

	if (LinePoint->Front == NULL)
	{
		LinePoint->Front = NewNode;
		LinePoint->Rear = NewNode;
	}
	else
	{
		LinePoint->Rear->Next = NewNode;
		LinePoint->Rear = NewNode;
	}

	(LinePoint->iWaitingPeople)++;
}

int DeleteNode(Line *LinePoint)
{
	if (LinePoint->Front == NULL)
		return -1;
	else
	{
		int iTmp = LinePoint->Front->iIdentifyCode;
		User *NodeTmp = LinePoint->Front;

		LinePoint->Front = LinePoint->Front->Next;
		delete NodeTmp;
		(LinePoint->iWaitingPeople)--;
		return iTmp;
	}
}

int SearchNode(Line *LinePoint, int Code)
{
	int iNumberOfPeople = 0;

	if (LinePoint->Front == NULL)
		return -1;

	User *UserTmp = LinePoint->Front;

	for (; ;)
	{
		if (UserTmp->iIdentifyCode == Code)
			return iNumberOfPeople;

		if (UserTmp->Next == NULL)
			break;

		iNumberOfPeople++;
		UserTmp = UserTmp->Next;
	}

	return -1;
}

int ReturnPeople(Line *LinePoint)
{
	return LinePoint->iWaitingPeople;
}