#pragma once
#include "Book.h"

enum SLOTSTATUS
{
	SLOTSTATUS_EMPTY,
	SLOTSTATUS_DELETED,
	SLOTSTATUS_INUSE
};

typedef double Key;

struct Slot
{
	Key kKey;
	Book *Value;
	SLOTSTATUS STATUS;
};