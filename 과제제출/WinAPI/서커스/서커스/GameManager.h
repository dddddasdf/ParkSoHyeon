#pragma once
#include "ResourceManager.h"
#include "TemplateSingleton.h"
#include "DrawManager.h"
#include "Player.h"

class GameManager : public Singleton <GameManager>
{
private:
	Player *m_PlayerData;

	bool m_IsMoving;	//�����̴� ������ üũ�ϴ� �뵵
	bool m_IsJumping;	//�����ϴ� ������ üũ�ϴ� �뵵
	bool m_IsHighest;	//������ �� Y�� ������ ���Ͽ� �ְ� ���� �����ߴ��� �ƴ��� Ȯ���ϱ�
public:
	void WholeInit(HWND hWnd);	//��ü �ʱ�ȭ �Ѱ�
	void MovingCharacter(const int& Key);	//ĳ���� �̵� ��Ű��
	void JumpingCharacter();	//ĳ���� ���� ��Ű��
	void ChangeCharacterYLocation();	//ĳ���� Y�� �����Ű��
	void StandingCharacter();	//ĳ���� �ٽ� �����
	void ChangeAnotherMotion();	//�ӽ�
	bool ReturnIsMoving() { return m_IsMoving; }
	bool ReturnIsJumping() { return m_IsJumping; }

	void DrawCharacterOrder(HDC *hdc, HWND hWnd);
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