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

	int m_BitMapNumberTmp;	//��Ʈ��(Ŭ����) �迭 �ε��� ȣ��� ��� ����
public:
	Object(HDC hdc);
	virtual ~Object() { };

	virtual void Update() = 0;
	virtual void Draw(HDC MemDCBack, const int& CharacterLocationX) = 0;

	int GetLocationX() { return m_LocationX; }
	int GetLocationY() { return m_LocationY; }

	void SetLocationX(const int& X) { m_LocationX = X; }
	void SetLocationY(const int& Y) { m_LocationY = Y; }

	HBITMAP ReturnMemberBitmap() { return m_ObjectBitMap[m_BitMapNumberTmp].ReturnBitMap(); }	//HBITMAP ��ȯ
	int ReturnMemberBitMapWidth() { return m_ObjectBitMap[m_BitMapNumberTmp].ReturnBitMapWidth(); }	//��Ʈ�� ���� ���� ��ȯ
	int ReturnMemberBitMapHeight() { return m_ObjectBitMap[m_BitMapNumberTmp].ReturnBitMapHeight(); }	//��Ʈ�� ���� ���� ��ȯ
};

class Ring1 : public Object
{
private:
	int m_AnimationState;	//�ִϸ��̼� ������ ���� ��� ����
	
	bool m_IsLeft;	//���� ���ʸ� ����� �ؾ� �� �������� ������ ������ �����ϴ� ��� ����
public:
	Ring1(HDC hdc, int X);
	~Ring1();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;

	void RingMoving(const int& MovePixel, const int& CharacterLocationX);
};

class LittleRing : public Object
{
private:
	bool m_IsLeft;	//���� ���ʸ� ����� �ؾ� �� �������� ������ ������ �����ϴ� �������
public:
	LittleRing(HDC hdc, int X);
	~LittleRing();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;

	void RingMoving(const int& MovePixel, const int& CharacterLocationX);
};

class Cash : public Object
{
private:
	bool m_IsSwitchOn;	//���� ���ָӴϰ� ���� �������� �ƴ��� �����ϴ� ��� ����
public:
	Cash(HDC hdc, int X);
	~Cash();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;

	void CashMoving(const int& MovePixel, const int& CharacterLocationX);
};

class MapTile : public Object
{
private:
	//Y��ǥ ���� �κ�
	int m_FloorYStart;	//�ٴ� Ÿ�� ���� Y��ǥ
	int m_CrowdYStart;	//���� Ÿ�� ���� Y��ǥ

	int m_CrowdWidth;
	int m_CrowdHeight;	//�̰͵��� �� �ʿ��մϱ�?->�ڳ����� �����̶� Ÿ�� ũ�� �޶� for�� ó���� �� ���� �߻���
public:
	MapTile(HDC hdc, int X);
	~MapTile();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
};

class Character : public Object
{
private:

public:
	Character(HDC hdc, int X);
	~
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