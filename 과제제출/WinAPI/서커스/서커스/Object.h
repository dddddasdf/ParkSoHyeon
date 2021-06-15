#pragma once
#include "BitMap.h"
#include "Defines.h"
#include "ResourceManager.h"

class Object
{
private:
	int m_LocationX;
	int m_LocationY;

protected:
	BitMap* m_ObjectBitMap;
	HDC m_MemDC;

public:
	Object(HDC hdc);
	virtual ~Object();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void GetMemDC() = 0;

	int GetLocationX() { return m_LocationX; }
	int GetLocationY() { return m_LocationY; }

	void SetLocationX(const int& X) { m_LocationX = X; }
	void SetLocationY(const int& Y) { m_LocationY = Y; }
};

class Ring1 : public Object
{
private:
	int m_AnimationState;	//애니메이션 관리를 위한 멤버변수

public:
	Ring1(HDC hdc, int X, int Y);
	virtual ~Ring1();

	void Update() { }
	void Draw(HDC MemDCBack, bool IsLeft);
	void GetMemDC() { }


};

class Ring2 : public Ring1
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