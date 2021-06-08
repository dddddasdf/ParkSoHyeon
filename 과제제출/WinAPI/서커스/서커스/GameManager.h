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


	int m_MovingDirection;	//�� ��ġ ������ ���� ���� ���� ��� ����

	bool m_IsDeadTrigger;	//��� ������ ��� ȭ�� ������ ��� ���߱� ���� ����, ������� ���� true �׾��� ���� false
public:
	void WholeInit(HWND hWnd);	//��ü �ʱ�ȭ �Ѱ�
	void MovingCharacter(const int& Key);	//ĳ���� �̵� ��Ű��
	void JumpingCharacter();	//ĳ���� ���� ��Ű��
	void ChangeCharacterYLocation();	//ĳ���� Y�� �����Ű��
	void StandingCharacter();	//ĳ���� ��� ����
	bool ReturnIsMoving() { return m_IsMoving; }
	bool ReturnIsJumping() { return m_IsJumping; }
	bool ReturnIsDead() { return m_IsDeadTrigger; }

	void CalculateRings(float elapsed);

	void CollisionCheck();	//�浹 üũ
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