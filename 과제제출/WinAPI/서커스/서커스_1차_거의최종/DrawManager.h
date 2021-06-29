#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"
#include "Object.h"

//#define Debug_Coll

class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;	//������ â ũ�� - ����
	int m_WindowHeight;	//������ â ũ�� - ����

	HDC m_MemDCBack;

	Ring1 *FireRing1;
	Ring1 *FireRing2;

	LittleRing* LittleFireRing;

	Cash* Cash1;

	MapTile* Map;

	Character* CharacterObject;

	BitMap LifeImage;

	HFONT m_FontCustomize;

	Fire* FireObjects;

	///////////////�ӽ�
	RECT Ring1RectDown;
	RECT Ring2RectDown;
	RECT LittleRingRectDown;
	RECT CharacterRect;

	///////////////////////////////////////////////////�̳�� �� ���� ����


	std::vector <int> m_ObstacleFireXLocation;	//��ֹ�-ȭ���� X��ǥ�� �����ϴ� ����<-���� �غ��ϱ� �̰� �� �ʿ䰡 ������ �ϴ� ���̷� ���ܵ�
	int m_FireAnimation;	//ȭ�� �ִϸ��̼� ������ ���� �������


	int m_FireSizeWidth;	//ȭ�� ���� ũ��
	int m_FireSizeHeight;	//ȭ�� ���� ũ��
public:
	void Init(HWND hWnd, HDC hdc);
	void DeadInit();	//�ƹ�ư �ε��ļ� �׾��� �� �Ϻκ� �ʱ�ȭ
	void DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation, const int& Life, const int& Score);

	void MoveRings(float MovingRingPixel, float MovingLittleRingPixel, int CharacterLocationX);	//�� ��ġ �ٲ��ֱ�

	bool IsCashCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//���ָӴϿ� �ε��ƴ��� üũ
	int IsObsjectCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//��ֹ��� �ε��ƴ���, �پ�Ѿ������� üũ��
	bool IsRingCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//���� �ε��ƴ��� üũ

	void DrawGameOver();	//���ӿ��� ȭ�� ���

	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);

	~DrawManager();
};
#define DrawMgr DrawManager::GetInstance()


/*
�����غ��� �׸� ������ BITMAP ���� ���� ũ�� �޴� �� �ʹ� ���ŷ��� �ʳ�?
��ü �ʱ�ȭ Ÿ�̹� �� ���������� ������ ��� �̹������� ������� ��� ������ �̸� �� �����صδ� �� ���� ��

ȭ�δ� ���� ���ݸ��� ���´�
�̰� ���� ��� ���� ���̳�... �÷��̾��� X��ǥ ���¿� ���� ���̵��� ������ �� ���ΰ�?
*/