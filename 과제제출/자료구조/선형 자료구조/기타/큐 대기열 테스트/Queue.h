#pragma once
#include "Headers.h"

struct User
{
	int iIdentifyCode;
	User *Next;
};

struct Line
{
	User *Front;
	User *Rear;
	int iWaitingPeople;
};

void InitLine(Line *LinePoint);

void AddNode(Line *LinePoint, int Code);

int DeleteNode(Line *LinePoint);

int SearchNode(Line *LinePoint, int Code);

int ReturnPeople(Line *LinePoint);