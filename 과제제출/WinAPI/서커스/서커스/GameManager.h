#pragma once
#include "ResourceManager.h"
#include "TemplateSingleton.h"
#include "DrawManager.h"
#include "Player.h"

class GameManager : public Singleton <GameManager>
{
private:
	Player *m_PlayerData;
public:
	void WholeInit();	//��ü �ʱ�ȭ �Ѱ�
	void MovingCharacter(int Key);	//ĳ���� �̵� ��Ű��
	void JumpingCharacter();	//ĳ���� ���� ��Ű��

	void DrawCharacterOrder(HDC *hdc);
};

#define GameMgr GameManager::GetInstance()


/*
�����غ��ϱ� ������ ���¿����� ����� ������ �̵����� �� �ϴ���
���۰��� ������ ���ΰ� ������ ���ΰ�
�����ϴ� �� �� ����� �� ������


ĳ���� X ��ǥ�� ����
Y��ǥ�� �����ÿ� �ٲ�

ĳ���� �̵� ��Ŀ����
����Ű �� �� ������ �����̰� �ٽ� ���ĵ����� ���ƿ��� �� 2�������� ����


������...
�����ϸ� ���� ���� ���� ���� �����
�����̽��� ������ ���� �ð����� ������ �ð� ���� Ű�Է� �� �޵��� ó����
�ؾ��� �� ����
*/