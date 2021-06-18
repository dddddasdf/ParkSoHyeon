#pragma once
#include "TemplateSingleton.h"
#include "Defines.h"
#include "BitMap.h"

class ResourceManager : public Singleton <ResourceManager>
{
private:
	std::vector <HBITMAP> m_BackgroundImageVector;
	std::vector <HBITMAP> m_ObstacleImageVector;
	std::vector <HBITMAP> m_CharacterImageVector;

	
public:
	void InitImages();
	HBITMAP ReturnCharacterImage(const int& MotionNumber);
	HBITMAP ReturnBackgroundImage(const int& BackgroundNumber);
	HBITMAP ReturnObstacleImage(const int& ObstacleNumber);

	BitMap ReturnCharacterBitMapClass(const int& ImageNumber);
	BitMap ReturnRingBitMapClass(const int& ImageNumber);
	BitMap ReturnLittleRingBitMapClass(const int& ImageNumber);
};

#define ResourceMgr ResourceManager::GetInstance()

/*
�̹����� ��� �����ϰ� ������ ���ΰ�..

���� ���� ġ�� �̹����� �ҷ����� ������ ��� �� ���ΰ�...
���͸� �������� �����ؼ� �θ��� �� �����鿡�� ���� �� ����
-��׶��� �̹���
-���ع�
-ĳ����

*/