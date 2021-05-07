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
만들어야 하는 함수
비트맵의 생성
비트맵에게 아이디 넘겨주기->define으로 대충 어쩌고 sprintf 머시기 저시기 와 완성
비트맵 파괴
기타 둥둥

*/