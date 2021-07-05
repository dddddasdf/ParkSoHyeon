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

	int m_BonusScore;	//���ʽ� ����
public:
	void WholeInit(HWND hWnd, HDC hdc);	//��ü �ʱ�ȭ �Ѱ�
	void PartialInit();	//ȭ�γ� ���� �ε������� �Ϻκ� �ʱ�ȭ
	void MovingCharacter(const int& Key);	//ĳ���� �̵� ��Ű��
	void JumpingCharacter();	//ĳ���� ���� ��Ű��
	void ChangeCharacterYLocation();	//ĳ���� Y�� �����Ű��
	void StandingCharacter();	//ĳ���� ��� ����
	bool ReturnIsMoving() { return m_IsMoving; }
	bool ReturnIsJumping() { return m_IsJumping; }
	bool ReturnIsDead() { return m_IsDeadTrigger; }

	void CalculateRings(float elapsed);
	void MinusBonusScore() { if (m_BonusScore > 0) m_BonusScore -= 10; }

	void CollisionCheck();	//�浹 üũ �Ѱ�
	bool GoalInCheck();	//���� üũ

	void Winning(HDC *hdc, HWND hWnd);	//���� ���� ��

	void DrawCharacterOrder(HDC *hdc, HWND hWnd) { DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation(), 
		m_PlayerData->ReturnLife(), m_PlayerData->ReturnScore(), m_BonusScore); }
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