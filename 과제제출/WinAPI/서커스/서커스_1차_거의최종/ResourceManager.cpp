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

	
	//장애물 이미지 파일 불러오기
	if (!m_ObstacleImageVector.empty())
		m_ObstacleImageVector.clear();

	m_ObstacleImageVector.push_back(NULL);	//번호 관리를 수월하게 하기 위해서 0번째 인덱스는 공백으로 채운다. 안 쓰는 번호임.

	//장애물-화로
	for (int i = OBSTACLE_FIRE_1; i <= OBSTACLE_FIRE_2; i++)
	{
		//고리 비트맵 불러와서 벡터에 저장하기
		std::string FileNameTmp = "fire_" + std::to_string(i);
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}
	
	//장애물-불고리 큰 거
	for (int i = OBSTACLE_RING_FIRST_1; i <= OBSTACLE_RING_SECOND_2; i++)
	{
		//고리 비트맵 불러와서 벡터에 저장하기
		std::string FileNameTmp = "ring_" + std::to_string(i - 2);
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}

	//장애물-불고리 작은 거
	for (int i = OBSTACLE_LITTLERING_1; i <= OBSTACLE_LITTLERING_2; i++)
	{
		//고리 비트맵 불러와서 벡터에 저장하기
		std::string FileNameTmp = "littlering_" + std::to_string(i - 6);
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}

	{
		//맞으면 죽는 장애물은 아니지만 돈주머니
		std::string FileNameTmp = "cash";
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
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

HBITMAP ResourceManager::ReturnObstacleImage(const int& ObstacleNumber)
{
	return m_ObstacleImageVector[ObstacleNumber];
}

BitMap ResourceManager::ReturnCharacterBitMapClass(const int& ImageNumber)
{
	std::string FileNameTmp = "player_" + std::to_string(ImageNumber);
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnRingBitMapClass(const int& ImageNumber)
{
	std::string FileNameTmp = "ring_" + std::to_string(ImageNumber);
	BitMap NewBitMapTmp(FileNameTmp);
	
	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnLittleRingBitMapClass(const int& ImageNumber)
{
	std::string FileNameTmp = "littlering_" + std::to_string(ImageNumber);
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnCashBitMapClass()
{
	std::string FileNameTmp = "cash";
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnMapTileBitMapClass(const int& ImageNumber)
{
	std::string FileNameTmp = "back_" + std::to_string(ImageNumber);
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnInterfaceBitMapClass(const int& ImageNumber)
{
	std::string FileNameTmp = "interface_" + std::to_string(ImageNumber);
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnGoalBitMapClass()
{
	std::string FileNameTmp = "goal";
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnPointBitMapClass()
{
	std::string FileNameTmp = "point";
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

BitMap ResourceManager::ReturnFireBitMapClass(const int& ImageNumber)
{
	std::string FileNameTmp = "fire_" + std::to_string(ImageNumber);
	BitMap NewBitMapTmp(FileNameTmp);

	return NewBitMapTmp;
}

/*

*/