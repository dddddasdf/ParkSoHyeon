#pragma once
#include "Book.h"

enum SLOTSTATUS
{
	SLOTSTATUS_EMPTY,
	SLOTSTATUS_DELETED,
	SLOTSTATUS_INUSE
};

typedef int Key;

struct Slot
{
	Key kKey;
	Book *Value;
	SLOTSTATUS STATUS;
};