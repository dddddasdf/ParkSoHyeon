#include "Functions.h"

void ListInit(LinkedList *List)
{
	List->Head = new Node;
	List->Current = NULL;
	List->Previous = NULL;
	List->Head->Next = NULL;

	List->NumberOfStock = 0;
}

void NodeInsert(LinkedList *List, Point *NewPoint)
{
	Node *NodeTmp = new Node;
	NodeTmp->Data = NewPoint;
	NodeTmp->Next = List->Head->Next;
	List->Head->Next = NodeTmp;
	(List->NumberOfStock)++;

	std::cout << "리스트에 저장 완료\n";
}

bool ListFirst(LinkedList *List, Point *Target)
{
	if (List->NumberOfStock == 0)
		return false;

	List->Current = List->Head->Next;
	List->Previous = List->Head;

	*Target = *(List->Current->Data);

	return true;
}

bool ListNext(LinkedList *List, Point *Target)
{
	if (List->Current->Next == NULL)
		return false;

	List->Previous = List->Current;
	List->Current = List->Current->Next;

	Target = List->Current->Data;

	return true;
}

Point* DeleteNode(LinkedList *List)
{
	Node *NodeTmp = List->Current;
	Point *PointTmp = List->Current->Data;
	List->Previous->Next = List->Current->Next;
	List->Current = List->Previous;
	
	delete NodeTmp;
	(List->NumberOfStock)--;

	return PointTmp;
}

int ShowStock(LinkedList *List)
{
	return List->NumberOfStock;
}

void DeleteAll(LinkedList *List)
{
	if (List->Head->Next != NULL)
	{
		List->Current = List->Head->Next;
		List->Previous = List->Head;

		while (1)
		{
			delete List->Previous;

			if (List->Current->Next == NULL)
				break;

			List->Previous = List->Current;
			List->Current = List->Current->Next;
		}

		delete List->Current;
	}
	else
		delete List->Head;
}