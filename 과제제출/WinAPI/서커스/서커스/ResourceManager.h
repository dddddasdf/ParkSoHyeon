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
	HBITMAP ReturnCharacterImage(int MotionNumber);
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