#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;
	int m_WindowHeight;

	std::vector <int> m_BackgroundTileVector;	//��� Ÿ���� ���ͷ� �����ϱ�
public:
	void Init(HWND hWnd);
	void DrawImages(HDC hdc, const int& MotionNumber, const int& YLocation);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
};
#define DrawMgr DrawManager::GetInstance()


/*


*/