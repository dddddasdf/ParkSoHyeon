#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"


class DrawManager : public Singleton <DrawManager>
{
private:
	int m_WindowWidth;	//������ â ũ�� - ����
	int m_WindowHeight;	//������ â ũ�� - ����

	int m_CharacterImageSizeWidth;	//ĳ���� ��Ʈ���� ���� ũ��
	int m_CharacterImageSizeHeight;	//ĳ���� ��Ʈ���� ���� ũ��

	int m_FloorImageSizeWidth;	//�ٴ� ��Ʈ���� ���� ũ��
	int m_FloorImageSizeHeight;	//�ٴ� ��Ʈ���� ���� ũ��

	int m_CrowdImageSizeWidth;	//���� ��Ʈ���� ���� ũ��
	int m_CrowdImageSizeHeight;	//���� ��Ʈ���� ���� ũ��-�ڳ����� 1�ȼ� �� ��� �ѵ� �������ϱ� �ڳ����� ���� ũ��� ����

	std::vector <int> m_BackgroundTileVector;	//��� Ÿ�� �� �ٴ� �κ��� ������ �κ��� ���ͷ� �����ϱ�

	int m_CrowdYStart;	//��濡�� ������ Y��ǥ ���� �κ�
	int m_FloorYStart;	//��濡�� �ٴ��� Y��ǥ ���� �κ�

	std::vector <int> m_ObstacleFireXLocation;	//��ֹ�-ȭ���� X��ǥ�� �����ϴ� ����<-���� �غ��ϱ� �̰� �� �ʿ䰡 ������ �ϴ� ���̷� ���ܵ�
	int m_FireAnimation;	//ȭ�� �ִϸ��̼� ������ ���� �������

	int m_Ring1XLocation;	//ù��° �� �� ��ġ�� �����ϴ� �������
	int m_Ring2XLocation;	//�ι�° �� �� ��ġ�� �����ϴ� �������
	int m_LittleRingXLocation;	//���� �� �� ��ġ�� �����ϴ� �������
	int m_RingAnimation;	//�� �ִϸ��̼� ������ ���� �������

public:
	void Init(HWND hWnd);
	void DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
};
#define DrawMgr DrawManager::GetInstance()


/*
�����غ��� �׸� ������ BITMAP ���� ���� ũ�� �޴� �� �ʹ� ���ŷ��� �ʳ�?
��ü �ʱ�ȭ Ÿ�̹� �� ���������� ������ ��� �̹������� ������� ��� ������ �̸� �� �����صδ� �� ���� ��

ȭ�δ� ���� ���ݸ��� ���´�
�̰� ���� ��� ���� ���̳�... �÷��̾��� X��ǥ ���¿� ���� ���̵��� ������ �� ���ΰ�?
*/