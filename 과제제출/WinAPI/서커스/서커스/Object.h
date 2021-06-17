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
	virtual ~Object() { };

	virtual void Update() = 0;
	virtual void Draw(HDC MemDCBack) = 0;

	int GetLocationX() { return m_LocationX; }
	int GetLocationY() { return m_LocationY; }

	void SetLocationX(const int& X) { m_LocationX = X; }
	void SetLocationY(const int& Y) { m_LocationY = Y; }
};

class Ring1 : public Object
{
private:
	int m_AnimationState;	//�ִϸ��̼� ������ ���� �������
	bool m_IsLeft;	//���� ���ʸ� ����� �ؾ� �� �������� ������ ������ �����ϴ� �������
public:
	Ring1(HDC hdc, int X);
	~Ring1();

	void Update() override { }
	void Draw(HDC MemDCBack) override;

	void MoveXPixel(int MovePixel, int CharacterLocationX);
};

class LittleRing : public Object
{
private:
	bool m_IsLeft;	//���� ���ʸ� ����� �ؾ� �� �������� ������ ������ �����ϴ� �������
public:
	LittleRing(HDC hdc, int X);
	~LittleRing();

	void Update() override { }
	void Draw(HDC MemDCBack) override;

	void MoveXPixel(int MovePixel, int CharacterLocationX);
};

//class Fire : public Object
//{
//private:
//
//public:
//	void Draw();
//};
//
//class Character : public Object
//{
//private:
//
//public:
//
//};