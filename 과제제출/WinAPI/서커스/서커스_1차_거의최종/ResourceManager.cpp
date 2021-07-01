#include "ResourceManager.h"

void ResourceManager::InitImages()
{
	//ĳ���� �̹��� ���� �ҷ�����
	if (!m_CharacterImageVector.empty())
		m_CharacterImageVector.clear();	//�ʱ�ȭ�� �� Ȥ�ó� ���Ͱ� �� ������ ���͸� �����ִ� �۾��� �ʿ���

	m_CharacterImageVector.push_back(NULL);	//��ȣ ������ �����ϰ� �ϱ� ���ؼ� 0��° �ε����� �������� ä���. �� ���� ��ȣ��.
	
	for (int i = 1; i <= 6; i++)
	{
		//ĳ���� ��Ʈ�� �ҷ��ͼ� ���Ϳ� �����ϱ�
		std::string FileNameTmp = "player_" + std::to_string(i);
		BitMap NewBitMapTmp(FileNameTmp);
		m_CharacterImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}


	//��� �̹��� ���� �ҷ�����
	if (!m_BackgroundImageVector.empty())
		m_BackgroundImageVector.clear();

	m_BackgroundImageVector.push_back(NULL);	//��ȣ ������ �����ϰ� �ϱ� ���ؼ� 0��° �ε����� �������� ä���. �� ���� ��ȣ��.

	for (int i = 1; i <= 4; i++)
	{
		//��� ��Ʈ�� �ҷ��ͼ� ���Ϳ� �����ϱ�
		std::string FileNameTmp = "back_" + std::to_string(i);
		BitMap NewBitMapTmp(FileNameTmp);
		m_BackgroundImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}

	
	//��ֹ� �̹��� ���� �ҷ�����
	if (!m_ObstacleImageVector.empty())
		m_ObstacleImageVector.clear();

	m_ObstacleImageVector.push_back(NULL);	//��ȣ ������ �����ϰ� �ϱ� ���ؼ� 0��° �ε����� �������� ä���. �� ���� ��ȣ��.

	//��ֹ�-ȭ��
	for (int i = OBSTACLE_FIRE_1; i <= OBSTACLE_FIRE_2; i++)
	{
		//�� ��Ʈ�� �ҷ��ͼ� ���Ϳ� �����ϱ�
		std::string FileNameTmp = "fire_" + std::to_string(i);
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}
	
	//��ֹ�-�Ұ� ū ��
	for (int i = OBSTACLE_RING_FIRST_1; i <= OBSTACLE_RING_SECOND_2; i++)
	{
		//�� ��Ʈ�� �ҷ��ͼ� ���Ϳ� �����ϱ�
		std::string FileNameTmp = "ring_" + std::to_string(i - 2);
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}

	//��ֹ�-�Ұ� ���� ��
	for (int i = OBSTACLE_LITTLERING_1; i <= OBSTACLE_LITTLERING_2; i++)
	{
		//�� ��Ʈ�� �ҷ��ͼ� ���Ϳ� �����ϱ�
		std::string FileNameTmp = "littlering_" + std::to_string(i - 6);
		BitMap NewBitMapTmp(FileNameTmp);
		m_ObstacleImageVector.push_back(NewBitMapTmp.ReturnBitMap());
	}

	{
		//������ �״� ��ֹ��� �ƴ����� ���ָӴ�
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