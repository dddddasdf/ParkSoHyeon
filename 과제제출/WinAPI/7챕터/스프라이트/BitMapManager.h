#pragma once
#include "BitMap.h"
#include <vector>
#include "TemplateSingleton.h"

enum CHARACTER_SIGHT
{
	CHARACTER_FRONT,
	CHARACTER_BACK,
	CHARACTER_LEFT,
	CHARACTER_RIGHT
};


class BitMapManager : public Singleton <BitMapManager>
{
private:

public:
	BitMapManager();
	HBITMAP LoadNewImage();
	void PrintBitMap(HDC hdc, const int& BitMapNumber, const int& xLocation, const int& yLocation);
	void PrintCharacter(HDC hdc, const int& CharacterSight, const int& CharacterMovement, const int& xLocation, const int& yLocation);
};

#define BitMapMgr BitMapManager::GetInstance()

/*
������ �ϴ� �Լ�
��Ʈ���� ����
��Ʈ�ʿ��� ���̵� �Ѱ��ֱ�->define���� ���� ��¼�� sprintf �ӽñ� ���ñ� �� �ϼ�
��Ʈ�� �ı�
��Ÿ �յ�

*/