#pragma once
#include "TemplateSingleton.h"
#include "Enums.h"
#include "BitMapManager.h"
#include "CardOrdering.h"

class GameManager : public Singleton <GameManager>
{
private:
	int m_NumberOfRevealed;	//���� "�ӽ÷�" �������� �ִ� ī���� ����
	int m_IndexFirst, m_IndexSecond;	//�������� �� �ε��� �޾ƿ��� �뵵
	int m_NumberOfCorrect;	//¦�� ���� ����
	bool m_IsPenalty;	//���� �߸��� ¦�� ã���� ��� Ȧ���
	int m_PenaltyTime;

public:
	void InitMemberVariable();	//������� �ʱ�ȭ

	bool ReturnIsPenalty() { return m_IsPenalty; }	//�І�Ƽ �������� ����
	void MouseLeftButtonAction(int MouseX, int MouseY);	//���콺 ���� ��ư ������ �� ������ �Լ�
	void PenaltyTimeAction();	//�г�Ƽ �ð� ���� �� ����
	bool IsAllCorrect();	//���� ¦�� ����°� Ȯ��
};
#define GameMgr GameManager::GetInstance()

/*
����Լ��� ��� ȣ���� ���ΰ�->���� �Լ��� �ϴ� �� �´� �� ����
�Ŵ����� ȣ���� ���ΰ�
������ ȣ���� ���ΰ�

*/

/*
��Ģ ���� ��Ī�� Penalty�� �Լ� ��Ī�� �� ��...


*/