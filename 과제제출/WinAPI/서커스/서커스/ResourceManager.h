#pragma once
#include "TemplateSingleton.h"
#include "Defines.h"

class ResourceManager : public Singleton <ResourceManager>
{
private:
	std::vector <HBITMAP> m_BackgroundImageVector;
	std::vector <HBITMAP> m_ObstacleImageVector;
	std::vector <HBITMAP> m_CharacterImageVector;

public:
	void InitImages();
};

#define ResourceMgr ResourceManager::GetInstance()

/*
이미지를 어떻게 저장하고 관리할 것인가..

벡터 쓴다 치면 이미지를 불러오는 순서를 어떻게 할 것인가...
벡터를 종류별로 분할해서 부르는 게 관리면에서 나을 것 같다
-백그라운드 이미지
-방해물
-캐릭터

*/