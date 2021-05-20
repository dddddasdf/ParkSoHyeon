#include "ResourceManager.h"

void ResourceManager::InitImages()
{
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
}


HBITMAP ResourceManager::ReturnCharacterImage(int MotionNumber)
{
	return m_CharacterImageVector[MotionNumber];
}

/*

*/