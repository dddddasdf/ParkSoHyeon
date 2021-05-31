#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;	//윈도우 창 크기 - 가로
	int m_WindowHeight;	//윈도우 창 크기 - 세로

	int m_CharacterImageSizeWidth;
	int m_CharacterImageSizeHeight;

	int m_FloorImageSizeWidth;
	int m_FloorImageSizeHeight;

	int m_CrowdImageSizeWidth;
	int m_CrowdImageSizeHeight;

	std::vector <int> m_BackgroundTileVector;	//배경 타일 중 바닥 부분을 제외한 부분을 벡터로 저장하기

	int m_CrowdYStart;	//배경에서 군중의 Y좌표 시작 부분
	int m_FloorYStart;	//배경에서 바닥의 Y좌표 시작 부분
public:
	void Init(HWND hWnd);
	void DrawImages(HDC hdc, const int& MotionNumber, const int& XLocation, const int& YLocation);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
};
#define DrawMgr DrawManager::GetInstance()


/*
생각해보니 그릴 때마다 BITMAP 변수 만들어서 크기 받는 거 너무 번거롭지 않나?
전체 초기화 타이밍 때 고정적으로 나오는 배경 이미지들의 사이즈는 멤버 변수로 미리 다 저장해두는 게 좋을 듯

*/