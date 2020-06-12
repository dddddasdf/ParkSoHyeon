#include "Data.h"

void SetData(Value *data, int i)
{
	data->iValue = i;
}

int ReturnData(Value *data)
{
	return (data->iValue);
}