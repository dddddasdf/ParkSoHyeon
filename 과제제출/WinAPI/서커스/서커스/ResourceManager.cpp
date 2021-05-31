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