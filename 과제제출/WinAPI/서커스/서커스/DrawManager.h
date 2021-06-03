#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;	//윈도우 창 크기 - 가로
	int m_WindowHeight;	//윈도우 창 크기 - 세로

	int m_CharacterImageSizeWidth;	//캐릭터 비트맵의 가로 크기
	int m_CharacterImageSizeHeight;	//캐릭터 비트맵의 세로 크기

	int m_FloorImageSizeWidth;	//바닥 비트맵의 가로 크기
	int m_FloorImageSizeHeight;	//바닥 비트맵의 세로 크기

	int m_CrowdImageSizeWidth;	//군중 비트맵의 가로 크기
	int m_CrowdImageSizeHeight;	//군중 비트맵의 세로 크기-코끼리가 1픽셀 더 길긴 한데 귀찮으니까 코끼리도 관중 크기로 관리

	std::vector <int> m_BackgroundTileVector;	//배경 타일 중 바닥 부분을 제외한 부분을 벡터로 저장하기

	int m_CrowdYStart;	//배경에서 군중의 Y좌표 시작 부분
	int m_FloorYStart;	//배경에서 바닥의 Y좌표 시작 부분

	std::vector <int> m_ObstacleFireXLocation;	//장애물-화로의 X좌표를 저장하는 벡터
	int m_FireAnimation;	//화로 애니메이션 조정을 위한 멤버변수

public:
	void Init(HWND hWnd);
	void DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
};
#define DrawMgr DrawManager::GetInstance()


/*
생각해보니 그릴 때마다 BITMAP 변수 만들어서 크기 받는 거 너무 번거롭지 않나?
전체 초기화 타이밍 때 고정적으로 나오는 배경 이미지들의 사이즈는 멤버 변수로 미리 다 저장해두는 게 좋을 듯

화로는 일정 간격마다 나온다
이걸 어찌 계산 돌릴 것이냐... 플레이어의 X좌표 상태에 따라 보이도록 말도록 할 것인가?
*/