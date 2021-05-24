#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:

public:
	void DrawImages(HDC hdc, HWND hWnd, const int& MotionNumber, const int& YLocation);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
};
#define DrawMgr DrawManager::GetInstance()


/*


*/