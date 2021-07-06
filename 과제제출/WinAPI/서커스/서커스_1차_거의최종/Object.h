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
	virtual void DrawFinal(HDC MemDCBack, const int& WindowWidth) = 0;

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
	bool m_IsGetScoreSwitch;	//���� ȹ�� ������ ���ؼ�... �ߺ� ȹ���ϸ� �� �ǹǷ� ������ �־��� ���ָӴϿ� �۵� ���� ����

	int m_DrawLocationApproach;	//�� ���� ���� �� ������ ��� ���
public:
	Ring1(HDC hdc, int X);
	~Ring1();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
	void DrawFinal(HDC MemDCBack, const int& WindowWidth) override;

	void RingMoving(const int& MovePixel, const int& CharacterLocationX);
	void RingMovingFinal(const int& MovePixel, const int& WindowWidth);	//�� ������ �κп� ���� �� �̵� �Լ�
	bool ReturnScoreSwitch() { return m_IsGetScoreSwitch; }
	void SwitchOffScore() { m_IsGetScoreSwitch = false; }
};

class LittleRing : public Object
{
private:
	bool m_IsLeft;	//���� ���ʸ� ����� �ؾ� �� �������� ������ ������ �����ϴ� �������
	bool m_IsGetScoreSwitch;	//���� ȹ�� ������ ���ؼ�... �ߺ� ȹ���ϸ� �� �ǹǷ� ������ �־��� ���ָӴϿ� �۵� ���� ����

	int m_DrawLocationApproach;	//�� ���� ���� �� ������ ��� ���
public:
	LittleRing(HDC hdc, int X);
	~LittleRing();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
	void DrawFinal(HDC MemDCBack, const int& WindowWidth) override;

	void RingMoving(const int& MovePixel, const int& CharacterLocationX);
	void RingMovingFinal(const int& MovePixel, const int& WindowWidth);	//�� ������ �κп� ���� �� �̵� �Լ�
	bool ReturnScoreSwitch() { return m_IsGetScoreSwitch; }
	void SwitchOffScore() { m_IsGetScoreSwitch = false; }
};

class Cash : public Object
{
private:
	bool m_IsSwitchOn;	//���� ���ָӴϰ� ���� �������� �ƴ��� �����ϴ� ��� ����

	int m_DrawLocationApproach;	//�� ���� ���� �� ������ ��� ���
public:
	Cash(HDC hdc, int X);
	~Cash();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
	void DrawFinal(HDC MemDCBack, const int& WindowWidth) override;

	void CashMoving(const int& MovePixel, const int& CharacterLocationX);
	void CashMovingFinal(const int& MovePixel, const int& WindowWidth);	//�� ������ �κп�����

	bool ReturnIsCashSwitched() { return m_IsSwitchOn; }
	void SwitchOffCash() { m_IsSwitchOn = false; }
	void SwitchOnCash() { m_IsSwitchOn = true; }
};

class MapTile : public Object
{
private:
	//Y��ǥ ���� �κ�
	int m_FloorYStart;	//�ٴ� Ÿ�� ���� Y��ǥ
	int m_CrowdYStart;	//���� Ÿ�� ���� Y��ǥ

	int m_CrowdWidth;
	int m_CrowdHeight;	//�̰͵��� �� �ʿ��մϱ�?->�ڳ����� �����̶� Ÿ�� ũ�� �޶� for�� ó���� ������ �߻���

	int m_StartBlockApproach;
	int m_CutWidthApproach;

	bool m_CrowdAnimation;	//�� �������� �� ���� �ִϸ��̼� �����
public:
	MapTile(HDC hdc, int X);
	~MapTile();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
	void DrawFinal(HDC MemDCBack, const int& WindowWidth) override;
	void DrawWin(HDC MemDCBack);	//�� �������� �� ���
};

class Character : public Object
{
private:
	
public:
	Character(HDC hdc, int X);
	~Character();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationY) override {  }	//�޾ƾ� �ϴ� �Ű������� �ٸ� ����� ����
	virtual void DrawFinal(HDC MemDCBack, const int& MapWidth) override {  }	//�̻� ����
	void DrawChracater(HDC MemDCBack, const int& CharacterLocationY, const int& MotionNumber);	//�� �����ϱ� ���� ���� ����ϴ� �Լ�
	void DrawCharacterFinal(HDC MemDCBack, const int& CharacterLocationX, const int& CharacterLocationY, const int& MotionNumber);	//�������� ���� �Լ�
	void DrawWin(HDC MemDCBack, const int& CharacterLocationX, const int& CharacterLocationY, const int& MotionNumber);	//�� �������� �� ���
};

class Goal : public Object
{
private:
	int m_DrawLocationApproach;	//�� ���� ���� �� ������ ��� ���

public:
	Goal(HDC hdc, int X);
	~Goal();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
	void DrawFinal(HDC MemDCBack, const int& WindowWidth) override;
};

class Fire : public Object
{
private:
	int m_AnimationState;	//�ִϸ��̼� ������ ���� ��� ����

	bool m_IsGetScoreSwitch;	//���� ȹ�� ������ ���ؼ�... �ߺ� ȹ���ϸ� �� �ǹǷ� ������ �־��� ���ָӴϿ� �۵� ���� ����

	int m_DrawLocationApproach;	//�� ���� ���� �� ������ ��� ���
public:
	Fire(HDC hdc, int X);
	~Fire();

	void Update() override { }
	void Draw(HDC MemDCBack, const int& CharacterLocationX) override;
	void DrawFinal(HDC MemDCBack, const int& WindowWidth) override;
	
	bool ReturnScoreSwitch() { return m_IsGetScoreSwitch; }
	void SwitchOffScore() { m_IsGetScoreSwitch = false; }
	void SwitchOnScore() { m_IsGetScoreSwitch = true; }
};

