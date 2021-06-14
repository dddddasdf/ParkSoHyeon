#pragma once
#include "BitMap.h"
#include "Defines.h"

class Object
{
private:
	int m_LocationX;
	int m_LocationY;

	BitMap m_ObjectBitMap;

protected:

public:
	virtual void Update() = 0;

	void SetBitMap(BitMap BitMapTmp) { m_ObjectBitMap = BitMapTmp; }

	void Draw(HDC MemDCBack);		//의미 없는 거 같은데 혹시 모르니 일단 유보
	int ReturnObjectWidth() { return m_ObjectBitMap.ReturnBitMapWidth(); }
	int ReturnObjectHeight() { return m_ObjectBitMap.ReturnBitMapHeight(); }

	int GetLocationX() { return m_LocationX; }
	int GetLocationY() { return m_LocationY; }

	void SetLocationX(int X) { m_LocationX = X; }
	void SetLocationY(int Y) { m_LocationY = Y; }
};

class Ring1 : public Object
{
private:

public:

};

class Ring2 : public Object
{
private:

public:

};

class LittleRing : public Object
{
private:

public:

};

class Fire : public Object
{
private:

public:
	void Draw();
};

class Character : public Object
{
private:

public:

};