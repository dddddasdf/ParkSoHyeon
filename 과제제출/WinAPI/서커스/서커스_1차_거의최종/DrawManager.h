#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"
#include "Object.h"


class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;	//윈도우 창 크기 - 가로
	int m_WindowHeight;	//윈도우 창 크기 - 세로

	HDC m_MemDCBack;

	Ring1 *FireRing1;
	Ring1 *FireRing2;

	LittleRing* LittleFireRing;

	Cash* Cash1;

	MapTile* Map;

	///////////////////////////////////////////////////이놈들 다 지울 예정

	int m_CharacterImageSizeWidth;	//캐릭터 비트맵의 가로 크기
	int m_CharacterImageSizeHeight;	//캐릭터 비트맵의 세로 크기

	int m_FloorImageSizeWidth;	//바닥 비트맵의 가로 크기
	int m_FloorImageSizeHeight;	//바닥 비트맵의 세로 크기

	int m_CrowdImageSizeWidth;	//군중 비트맵의 가로 크기
	int m_CrowdImageSizeHeight;	//군중 비트맵의 세로 크기-코끼리가 1픽셀 더 길긴 한데 귀찮으니까 코끼리도 관중 크기로 관리

	std::vector <int> m_BackgroundTileVector;	//배경 타일 중 바닥 부분을 제외한 부분을 벡터로 저장하기

	int m_CrowdYStart;	//배경에서 군중의 Y좌표 시작 부분
	int m_FloorYStart;	//배경에서 바닥의 Y좌표 시작 부분

	std::vector <int> m_ObstacleFireXLocation;	//장애물-화로의 X좌표를 저장하는 벡터<-막상 해보니까 이거 쓸 필요가 없었네 일단 더미로 남겨둠
	int m_FireAnimation;	//화로 애니메이션 조정을 위한 멤버변수

	int m_Ring1XLocation;	//첫번째 불 고리 위치를 조정하는 멤버변수
	int m_Ring2XLocation;	//두번째 불 고리 위치를 조정하는 멤버변수
	int m_LittleRingXLocation;	//작은 불 고리 위치를 조정하는 멤버변수
	int m_RingAnimation;	//고리 애니메이션 조정을 위한 멤버변수

	int m_CashSizeWidth;	//돈주머니 가로 크기
	int m_CashSizeHeight;	//돈주머니 세로 크기
	bool m_IsCashSwitchOn;	//돈주머니가 먹혔는지 아닌지 테스트하는 것

	int m_FireSizeWidth;	//화로 가로 크기
	int m_FireSizeHeight;	//화로 세로 크기
public:
	void Init(HWND hWnd, HDC hdc);
	void DeadInit();	//아무튼 부딪쳐서 죽었을 때 일부분 초기화
	void DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);

	void MoveRings(float MovingRingPixel, float MovingLittleRingPixel, int CharacterLocationX);	//링 위치 바꿔주기

	bool IsCashCollision(const int& MotionNumber, const int& CharacterYLocation);	//돈주머니와 부딪쳤는지 체크
	bool IsObstacleCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//화로와 부딪쳤는지 체크+걍 장애물 전반으로 변경함
	bool IsRingCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//고리와 부딪쳤는지 체크

	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);

	~DrawManager();
};
#define DrawMgr DrawManager::GetInstance()


/*
생각해보니 그릴 때마다 BITMAP 변수 만들어서 크기 받는 거 너무 번거롭지 않나?
전체 초기화 타이밍 때 고정적으로 나오는 배경 이미지들의 사이즈는 멤버 변수로 미리 다 저장해두는 게 좋을 듯

화로는 일정 간격마다 나온다
이걸 어찌 계산 돌릴 것이냐... 플레이어의 X좌표 상태에 따라 보이도록 말도록 할 것인가?
*/