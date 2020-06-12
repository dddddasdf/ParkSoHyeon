#pragma once
#include "Point.h"

struct Node
{
	Point* Data;
	Node *Next;
};

struct LinkedList
{
	Node *Head;
	Node *Current;
	Node *Previous;

	int NumberOfStock;
};

void ListInit(LinkedList *List);

void NodeInsert(LinkedList *List, Point *NewPoint);

bool ListFirst(LinkedList *List, Point *Target);
bool ListNext(LinkedList *List, Point *Target);

Point* DeleteNode(LinkedList *List);

int ShowStock(LinkedList *List);

void DeleteAll(LinkedList *List);