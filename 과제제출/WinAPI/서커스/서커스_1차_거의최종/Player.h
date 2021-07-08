#pragma once
#include "Defines.h"


class Player
{
private:
	int m_PlayerLife;
	int m_PlayerScore;
	int m_PlayerMotion;
	int m_PlayerYLocation;	//ȭ�鿡�� ���̴� �÷��̾��� Y��ǥ.
	int m_PlayerXLocation;	//��ü �� ���̿��� �÷��̾ ���� ��ġ�� X��ǥ. ȭ�鿡�� ���̴� ��ġ�� X��ǥ�� �ƴ�.
	int m_PlayerDirection;
public:
	Player() { InitPlayer(); }

	void InitPlayer();
	void DeadInit();	//�ƹ�ư �ε��ļ� �׾��� �� �Ϻκ� �ʱ�ȭ
	void ChangeMotion(const int& State);
	void ChangeXLocation(const int& Key);
	void ChangeYLocation(bool IsUp);

	int ReturnMotion() { return m_PlayerMotion; }
	int ReturnCharacterXLocation() { return m_PlayerXLocation; }
	int ReturnCharacterYLocation() { return m_PlayerYLocation; }
	int ReturnScore() { return m_PlayerScore; }
	int ReturnLife() { return m_PlayerLife; }
	void MinusLife() { m_PlayerLife--; }	//����� ��� �پ��
	void PlusScore(const int& Score) { m_PlayerScore += Score; }
	
	void SetYLocation(const int& Y) {
		m_PlayerYLocation = Y; //���ν� ������ y��ǥ ����
	}
};

