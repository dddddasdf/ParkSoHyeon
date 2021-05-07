#include "GameManager.h"


void GameManager::InitMemberVariable()
{
	m_NumberOfRevealed = 0;
	m_IndexFirst = NO_INDEX;
	m_IndexSecond = NO_INDEX;	//�������� �� �ε��� �޾ƿ��� �뵵
	m_NumberOfCorrect = 0;	//���� ����
	m_IsPenalty = false;	//���� �߸��� ¦�� ã���� ��� Ȧ���
	m_PenaltyTime = 0;
}


void GameManager::MouseLeftButtonAction(const int& MouseX, const int& MouseY)
{
	int i = CardMgr->CheckOverlap(MouseX, MouseY);

	if (i != NO_INDEX)
	{
		if (m_NumberOfRevealed == 0)
			m_IndexFirst = i;
		else
			m_IndexSecond = i;

		m_NumberOfRevealed++;
	}

	//������ ī���� ������ 2���� �Ǿ��ٸ� ��ġ�ϴ��� üũ��
	if (m_NumberOfRevealed == 2)
	{
		if (CardMgr->IsCorrect(m_IndexFirst, m_IndexSecond))
		{
			//��ġ�� ���� ������ �ø��� ������ ���� ���� �ʱ�ȭ
			m_NumberOfCorrect++;
			m_NumberOfRevealed = 0;
			m_IndexFirst = NO_INDEX;
			m_IndexSecond = NO_INDEX;
		}
		else
		{
			m_IsPenalty = true;	//Ʋ�ȴٸ� bool ������ true�� Ȱ��ȭ ��Ű�� Ÿ�̸� �۵�
		}
	}
}


void GameManager::PenaltyTimeAction()
{
	m_PenaltyTime++;

	if (m_PenaltyTime == INCORRECT_TIME)
	{
		//��Ģ �ð��� �� �Ǹ� ���󺹱�
		CardMgr->CardReset(m_IndexFirst, m_IndexSecond);
		m_IsPenalty = false;
		m_PenaltyTime = 0;
		m_NumberOfRevealed = 0;
		m_IndexFirst = NO_INDEX;
		m_IndexSecond = NO_INDEX;
	}
}

bool GameManager::IsAllCorrect()
{
	if (m_NumberOfCorrect == NUMBER_OF_PAIR)
		return true;
	else
		return false;
}