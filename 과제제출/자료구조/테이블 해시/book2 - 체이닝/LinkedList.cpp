#include "LinkedList.h"

void ListInit(List *ListTmp)
{
	ListTmp->HeadNode = new Node;
	ListTmp->HeadNode->Next = NULL;
	ListTmp->HeadNode->Previous = NULL;
	(ListTmp->HeadNode->Next)->Previous = ListTmp->HeadNode;
	ListTmp->CurrentNode = NULL;
	ListTmp->CompareFunction = NULL;
	ListTmp->iNumberOfData = 0;
}

void SetCompareFunction(List *ListTmp, int(*FunctionTmp)(int, int))
{
	ListTmp->CompareFunction = FunctionTmp;
}

void ListInsert(List *ListTmp, Slot SlotTmp)
{
	if (ListTmp->HeadNode->Next == NULL)
		FirstInsert(ListTmp, SlotTmp);
	else
		SecondInsert(ListTmp, SlotTmp);
}

void FirstInsert(List *ListTmp, Slot SlotTmp)
{
	Node *NewNode = new Node;
	NewNode->Data = SlotTmp;
	NewNode->Previous = ListTmp->HeadNode;
	NewNode->Next = ListTmp->HeadNode->Next;
	(NewNode->Next)->Previous = NewNode;
	ListTmp->HeadNode->Next = NewNode;

	(ListTmp->iNumberOfData)++;
}

void SecondInsert(List *ListTmp, Slot SlotTmp)
{
	Node *NewNode = new Node;
	NewNode->Data = SlotTmp;
	
	ListTmp->CurrentNode = ListTmp->HeadNode;
	int iIsCompare = 0;

	while (ListTmp->CurrentNode != NULL)
	{
		iIsCompare = ListTmp->CompareFunction(SlotTmp.kKey, ListTmp->CurrentNode->Data.kKey);

		if (iIsCompare == COMPARE_SMALL)
			break;
		else if (iIsCompare == COMPARE_EQUALL)
		{
			NewNode->Data.
		}
		
		ListTmp->CurrentNode = ListTmp->CurrentNode->Next;
	}

	NewNode->Previous = ListTmp->CurrentNode->Previous;
	NewNode->Next = ListTmp->CurrentNode;
	(ListTmp->CurrentNode->Previous)->Next = NewNode;
	(ListTmp->CurrentNode)->Previous = NewNode;
	(ListTmp->iNumberOfData)++;
}

bool ListFirst(List *ListTmp, Slot *SlotTmp);
bool ListSecond(List *ListTmp, Slot *SlotTmp);

