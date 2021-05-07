#include "GameManager.h"


void GameManager::InitMemberVariable()
{
	m_NumberOfRevealed = 0;
	m_IndexFirst = NO_INDEX;
	m_IndexSecond = NO_INDEX;	//뒤집었을 때 인덱스 받아오는 용도
	m_NumberOfCorrect = 0;	//맞춘 개수
	m_IsPenalty = false;	//만약 잘못된 짝을 찾았을 경우 홀드용
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

	//뒤집힌 카드의 개수가 2개가 되었다면 일치하는지 체크함
	if (m_NumberOfRevealed == 2)
	{
		if (CardMgr->IsCorrect(m_IndexFirst, m_IndexSecond))
		{
			//일치시 맞힌 개수를 늘리고 뒤집기 관련 변수 초기화
			m_NumberOfCorrect++;
			m_NumberOfRevealed = 0;
			m_IndexFirst = NO_INDEX;
			m_IndexSecond = NO_INDEX;
		}
		else
		{
			m_IsPenalty = true;	//틀렸다면 bool 변수를 true로 활성화 시키고 타이머 작동
		}
	}
}


void GameManager::PenaltyTimeAction()
{
	m_PenaltyTime++;

	if (m_PenaltyTime == INCORRECT_TIME)
	{
		//벌칙 시간이 다 되면 원상복귀
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