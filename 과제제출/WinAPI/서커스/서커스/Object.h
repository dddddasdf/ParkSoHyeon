#pragma once
#include "BitMap.h"

class Object
{
private:
	int m_LocationX;
	int m_LocationY;

	BitMap m_ObjectBitMap;

protected:

public:
	virtual void Update() = 0;

	int ReturnObjectWidth() { return m_ObjectBitMap.ReturnBitMapWidth(); }
	int ReturnObjectHeight() { return m_ObjectBitMap.ReturnBitMapHeight(); }
};

class Ring1 : public Object
{

};