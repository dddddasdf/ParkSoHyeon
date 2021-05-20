#pragma once
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:

public:
	void DrawImages(HDC hdc, int MotionNumber, int YLocation);
};
#define DrawMgr DrawManager::GetInstance()


/*


*/