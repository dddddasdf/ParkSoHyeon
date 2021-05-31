#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;	//������ â ũ�� - ����
	int m_WindowHeight;	//������ â ũ�� - ����

	int m_CharacterImageSizeWidth;
	int m_CharacterImageSizeHeight;

	int m_FloorImageSizeWidth;
	int m_FloorImageSizeHeight;

	int m_CrowdImageSizeWidth;
	int m_CrowdImageSizeHeight;

	std::vector <int> m_BackgroundTileVector;	//��� Ÿ�� �� �ٴ� �κ��� ������ �κ��� ���ͷ� �����ϱ�

	int m_CrowdYStart;	//��濡�� ������ Y��ǥ ���� �κ�
	int m_FloorYStart;	//��濡�� �ٴ��� Y��ǥ ���� �κ�
public:
	void Init(HWND hWnd);
	void DrawImages(HDC hdc, const int& MotionNumber, const int& XLocation, const int& YLocation);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
};
#define DrawMgr DrawManager::GetInstance()


/*
�����غ��� �׸� ������ BITMAP ���� ���� ũ�� �޴� �� �ʹ� ���ŷ��� �ʳ�?
��ü �ʱ�ȭ Ÿ�̹� �� ���������� ������ ��� �̹������� ������� ��� ������ �̸� �� �����صδ� �� ���� ��

*/