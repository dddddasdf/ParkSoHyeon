#include "ResourceManager.h"

void ResourceManager::InitImages()
{
	//캐릭터 이미지 파일 불러오기
	if (!m_CharacterImageVector.empty())
		m_CharacterImageVector.clear();	//초기화할 때 혹시나 벡터가 차 있으면 벡터를 지워주는 작업이 필요함

	m_CharacterImageVector.push_back(NULL);	//번호 관리를 수월하게 하기 위해서 0번째 인덱스는 공백으로 채운다. 안 쓰는 번호임.
	
	for (int i = 1; i <= 6; i++)
	{
		//캐릭터 비트맵 불러와서 벡터에 저장하기
		std::string FileNameTmp = "player_" + std::to_string(i);
		BitMap NewBitMapTmp(FileNameTmp);
		m_CharacterImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}


	//배경 이미지 파일 불러오기
	if (!m_BackgroundImageVector.empty())
		m_BackgroundImageVector.clear();

	m_BackgroundImageVector.push_back(NULL);	//번호 관리를 수월하게 하기 위해서 0번째 인덱스는 공백으로 채운다. 안 쓰는 번호임.

	for (int i = 1; i <= 4; i++)
	{
		//배경 비트맵 불러와서 벡터에 저장하기
		std::string FileNameTmp = "back_" + std::to_string(i);
		BitMap NewBitMapTmp(FileNameTmp);
		m_BackgroundImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}

	
}


HBITMAP ResourceManager::ReturnCharacterImage(const int& MotionNumber)
{
	return m_CharacterImageVector[MotionNumber];
}

HBITMAP ResourceManager::ReturnBackgroundImage(const int& BackgroundNumber)
{
	return m_BackgroundImageVector[BackgroundNumber];
}

/*

*/