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

	int m_BitMapNumberTmp;	//비트맵(클래스) 배열 인덱스 호출용 멤버 변수
public:
	Object(HDC hdc);
	virtual ~Object() { };

	virtual void Update() = 0;
	virtual void Draw(HDC MemDCBack, const int& CharacterLocationX) = 0;

	int GetLocationX() { return m_LocationX; }
	int GetLocationY() { return m_LocationY; }

	void SetLocationX(const int& X) { m_LocationX = X; }
	void SetLocationY(const int& Y) { m_LocationY = Y; }

	HBITMAP ReturnMemberBitmap() { return m_ObjectBitMap[m_BitMapNumberTmp].ReturnBitMap(); }	//HBITMAP 반환
	int ReturnMemberBitMapWidth() { return m_ObjectBitMap[m_BitMapNumberTmp].ReturnBitMapWidth(); }	//비트맵 가로 길이 반환
	int ReturnMemberBitMapHeight() { return m_ObjectBitMap[m_BitMapNumberTmp].ReturnBitMapHeight(); }	//비트맵 세로 길이 반환
};

class Ring1 : public Object
{
private:
	int m_AnimationState;	//애니메이션 관리를 위한 멤버 변수
	
	bool m_IsLeft;	//현재 왼쪽면 출력을 해야 할 차례일지 오른쪽 면인지 구분하는 멤버 변수
	bool m_IsGetScoreSwitch;	//점수 획득 관리를 위해서... 중복 획득하면 안 되므로 변수를 넣었다 돈주머니와 작동 원리 같음
public:
	Ring1(HDC hdc, int X);
	~Ring1();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;

	void RingMoving(const int& MovePixel, const int& CharacterLocationX);
	bool ReturnScoreSwitch() { return m_IsGetScoreSwitch; }
	void SwitchOffScore() { m_IsGetScoreSwitch = false; }
};

class LittleRing : public Object
{
private:
	bool m_IsLeft;	//현재 왼쪽면 출력을 해야 할 차례일지 오른쪽 면인지 구분하는 멤버변수
	bool m_IsGetScoreSwitch;	//점수 획득 관리를 위해서... 중복 획득하면 안 되므로 변수를 넣었다 돈주머니와 작동 원리 같음
public:
	LittleRing(HDC hdc, int X);
	~LittleRing();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;

	void RingMoving(const int& MovePixel, const int& CharacterLocationX);
	bool ReturnScoreSwitch() { return m_IsGetScoreSwitch; }
	void SwitchOffScore() { m_IsGetScoreSwitch = false; }
};

class Cash : public Object
{
private:
	bool m_IsSwitchOn;	//현재 돈주머니가 먹힌 상태인지 아닌지 구분하는 멤버 변수
public:
	Cash(HDC hdc, int X);
	~Cash();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;

	void CashMoving(const int& MovePixel, const int& CharacterLocationX);

	bool ReturnIsCashSwitched() { return m_IsSwitchOn; }
	void SwitchOffCash() { m_IsSwitchOn = false; }
	void SwitchOnCash() { m_IsSwitchOn = true; }
};

class MapTile : public Object
{
private:
	//Y좌표 시작 부분
	int m_FloorYStart;	//바닥 타일 시작 Y좌표
	int m_CrowdYStart;	//관중 타일 시작 Y좌표

	int m_CrowdWidth;
	int m_CrowdHeight;	//이것들이 왜 필요합니까?->코끼리랑 군중이랑 타일 크기 달라서 for문 처리시 대참사 발생함
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
	~Character();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationY) override {  }	//받아야 하는 매개변수가 다른 관계로 더미
	void DrawChracater(HDC MemDCBack, const int& CharacterLocationY, const int& MotionNumber);
};

class Goal : public Object
{
private:

public:
	Goal(HDC hdc, int X);
	~Goal();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationY) override {}
};

class Fire : public Object
{
private:
	int m_AnimationState;	//애니메이션 관리를 위한 멤버 변수

	bool m_IsGetScoreSwitch;	//점수 획득 관리를 위해서... 중복 획득하면 안 되므로 변수를 넣었다 돈주머니와 작동 원리 같음
public:
	Fire(HDC hdc, int X);
	~Fire();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationY) override;
};

