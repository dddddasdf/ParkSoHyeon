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
	
	ListTmp->CurrentNode = ListTmp->HeadNode;
	int iIsCompare = 0;

	while (ListTmp->CurrentNode != NULL)
	{
		iIsCompare = ListTmp->CompareFunction(SlotTmp.Value->kKDC, ListTmp->CurrentNode->Data.Value->kKDC);

		if (iIsCompare == COMPARE_SMALL)
			break;
		else if (iIsCompare == COMPARE_EQUALL)
		{
			int iTmp = 0;
			double dTmp = 0;
			iTmp = (int)SlotTmp.Value->kKDC;
			dTmp = SlotTmp.Value->kKDC - iTmp;
			dTmp = (dTmp / 10) + iTmp;	//KDC가 중복되면 소수점 아래를 1/10 해준다
			SlotTmp.Value->kKDC = dTmp;
			
			std::cout << "기존에 중복되는 KDC 번호 존재... KDC 변경: " << dTmp << "\n";
		}
		
		ListTmp->CurrentNode = ListTmp->CurrentNode->Next;
	}

	NewNode->Data = SlotTmp;

	NewNode->Previous = ListTmp->CurrentNode->Previous;
	NewNode->Next = ListTmp->CurrentNode;
	(ListTmp->CurrentNode->Previous)->Next = NewNode;
	(ListTmp->CurrentNode)->Previous = NewNode;
	(ListTmp->iNumberOfData)++;
}

bool ListFirst(List *ListTmp, Slot *SlotTmp);
bool ListSecond(List *ListTmp, Slot *SlotTmp);

