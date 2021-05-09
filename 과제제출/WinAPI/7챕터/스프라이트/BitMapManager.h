#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "BitMap.h"
#include "Definition.h"
#include <vector>
#include <windows.h>
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
	void PrintCharacter(HDC hdc, const int& CharacterSight, const int& xLocation, const int& yLocation);
};

#define BitMapMgr BitMapManager::GetInstance()

/*



*/