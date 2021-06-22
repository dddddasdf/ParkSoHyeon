#pragma once
#pragma comment (lib, "Msimg32.lib")
#include "Defines.h"
#include "ResourceManager.h"
#include "Object.h"


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

	///////////////////////////////////////////////////�̳�� �� ���� ����

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

	int m_CashSizeWidth;	//���ָӴ� ���� ũ��
	int m_CashSizeHeight;	//���ָӴ� ���� ũ��
	bool m_IsCashSwitchOn;	//���ָӴϰ� �������� �ƴ��� �׽�Ʈ�ϴ� ��

	int m_FireSizeWidth;	//ȭ�� ���� ũ��
	int m_FireSizeHeight;	//ȭ�� ���� ũ��
public:
	void Init(HWND hWnd, HDC hdc);
	void DeadInit();	//�ƹ�ư �ε��ļ� �׾��� �� �Ϻκ� �ʱ�ȭ
	void DrawImages(HDC hdc, const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);

	void MoveRings(float MovingRingPixel, float MovingLittleRingPixel, int CharacterLocationX);	//�� ��ġ �ٲ��ֱ�

	bool IsCashCollision(const int& MotionNumber, const int& CharacterYLocation);	//���ָӴϿ� �ε��ƴ��� üũ
	bool IsObstacleCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//ȭ�ο� �ε��ƴ��� üũ+�� ��ֹ� �������� ������
	bool IsRingCollision(const int& MotionNumber, const int& CharacterXLocation, const int& CharacterYLocation);	//���� �ε��ƴ��� üũ

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