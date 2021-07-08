#include "GameManager.h"

void GameManager::WholeInit(HWND hWnd, HDC hdc)
{
	ResourceMgr->InitImages();
	DrawMgr->Init(hWnd, hdc);
	m_PlayerData = new Player;
	m_IsMoving = false;
	m_IsJumping = false;
	m_IsHighest = false;
	m_MovingDirection = NULL;
	m_IsDeadTrigger = false;
	m_BonusScore = BONUS_SCORE;
	m_NowState = STATE_NONE;
}

void GameManager::PartialInit()
{
	DrawMgr->DeadInit();
	m_PlayerData->DeadInit();
	
	m_IsMoving = false;
	m_IsJumping = false;
	m_IsHighest = false;
	m_MovingDirection = NULL;
	m_IsDeadTrigger = false;
	m_BonusScore = BONUS_SCORE;
	m_NowState = STATE_NONE;
}

void GameManager::MovingCharacter(const int& Key)
{
	switch (Key)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_PlayerData->ChangeMotion(MOTION_RUNNING);
		m_PlayerData->ChangeXLocation(Key);
		m_IsMoving = true;
		break;
	}
}

void GameManager::JumpingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_JUMPING);

	m_IsJumping = true;
}

void GameManager::ChangeCharacterYLocation()
{
	/*
	m_IsHighest를 통해 고도를 조절한다. 
	false일 때 고도를 순차적으로 올리고 최고 고도에 도달하면 m_IsHighest를 true로 교체한 다음 고도를 순차적으로 내린다
	지평선 좌표에 도달하면 m_IsHighest를 false로 돌리고 m_IsJumping 또한 false로 돌린 다음 마지막으로 캐릭터의 모션을 스탠딩으로 교체한다
	*/
	
	switch (m_IsHighest)
	{
	case false:
	{
		m_PlayerData->ChangeYLocation(true);
		if (JUMP_HEIGHT >= m_PlayerData->ReturnCharacterYLocation())
		{
			m_IsHighest = true;
		}
	}
		break;
	case true:
	{
		m_PlayerData->ChangeYLocation(false);
		if (LOCATION_CHARACTER_HORIZON <= m_PlayerData->ReturnCharacterYLocation())
		{
			m_IsHighest = false;
			m_IsJumping = false;
			StandingCharacter();
		}
	}
		break;
	}
}

void GameManager::StandingCharacter()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		switch (m_PlayerData->ReturnMotion())
		{
		case MOTION_JUMPING:
			m_PlayerData->ChangeMotion(MOTION_RUNNING);
			break;
		case MOTION_RUNNING:
			m_PlayerData->ChangeMotion(MOTION_JUMPING);
			break;
		}
		m_MovingDirection = VK_RIGHT;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		switch (m_PlayerData->ReturnMotion())
		{
		case MOTION_STAND:
			m_PlayerData->ChangeMotion(MOTION_RUNNING);
			break;
		case MOTION_RUNNING:
			m_PlayerData->ChangeMotion(MOTION_STAND);
			break;
		}
		m_MovingDirection = VK_LEFT;
	}
	else
	{
		m_PlayerData->ChangeMotion(MOTION_STAND);
		m_MovingDirection = NULL;
	}
		

	/*
	지금 보니까 모션이 달리는 중에는 캐릭터 스프라이트 2, 3이 번갈아가면서 나오더라
	일단 구현을 위해서 이렇게 하였다... 모션을 바꾸는 함수인 이 함수가 호출되는 순간 키입력이 지속적으로 이루어지고 있다면 다른 달리는 모션으로
	없다면 스탠딩으로
	*/

	m_IsMoving = false;
}

void GameManager::CalculateRings(float elapsed)
{
	bool Tmp = DrawMgr->IsFinal(m_PlayerData->ReturnCharacterXLocation());	//맵 끝부분은 스크롤하지 않으므로 가속이나 감속이 이루어지면 안 된다 그러기 위해 맵 끝부분인지 확인하는 임시 변수
	
	auto addSpeed = MOVE_PIXEL * 5;
	if (m_MovingDirection == VK_RIGHT && false == Tmp)
	{
		//MOVE_PIXEL * 40;
		DrawMgr->MoveRings((RING_MOVE_PIXEL + addSpeed) * elapsed, (LITTLERING_MOVE_PIXEL + addSpeed) * elapsed, m_PlayerData->ReturnCharacterXLocation());
	}
	else if (m_MovingDirection == VK_LEFT && m_PlayerData->ReturnCharacterXLocation() > 0 && false == Tmp)
	{
		DrawMgr->MoveRings((RING_MOVE_PIXEL - addSpeed) * elapsed, (LITTLERING_MOVE_PIXEL - addSpeed) * elapsed, m_PlayerData->ReturnCharacterXLocation());
	}
	else
		DrawMgr->MoveRings(RING_MOVE_PIXEL * elapsed, LITTLERING_MOVE_PIXEL * elapsed, m_PlayerData->ReturnCharacterXLocation());


	/*
	처음에는 이 함수에서 키입력을 받을려고 했지만 그 경우 점프 동안 방향키를 바꿔버리면 링의 속도도 달라지는 대참사 발생
	그런 고로 움직이는 함수에서 멤버 변수에 어느 방향으로 움직이고 있다는 것을 저장하여 그 변수를 이용하여 링의 움직임을 교체하도록 함

	구현하긴 했는데 나 자신도 원리를 모르겠는 기적의 구현
	*/
}

void GameManager::CollisionCheck()
{
	if (DrawMgr->IsCashCollision(m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation()))
		m_PlayerData->PlusScore(SCORE_CASH);
	
	int Tmp = DrawMgr->IsObsjectCollision(m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation());

	if (CRASHED_OBJECT == Tmp)
	{
		m_PlayerData->ChangeMotion(MOTION_DEAD);
		m_IsDeadTrigger = true;
		m_NowState = STATE_DEAD;
		m_PlayerData->MinusLife();
	}
	else
		m_PlayerData->PlusScore(Tmp);
}

void GameManager::GoalInCheck()
{
	if (DrawMgr->IsInGoal_In(m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation()))
	{
		m_PlayerData->SetYLocation(353);
		GameMgr->ChangeWinningMotion();
		m_NowState = STATE_WIN;
	}
}

void GameManager::Winning(HDC *hdc)
{
	DrawMgr->DrawWinImages(*hdc, m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation(),
		m_PlayerData->ReturnLife(), m_PlayerData->ReturnScore(), m_BonusScore, m_PlayerData->ReturnMotion());
}

void GameManager::ChangeWinningMotion()
{
	if (m_PlayerData->ReturnMotion() == MOTION_WIN1)
		m_PlayerData->ChangeMotion(MOTION_WIN2);
	else
		m_PlayerData->ChangeMotion(MOTION_WIN1);
}

void GameManager::CaculatingScore()
{
	if (m_BonusScore > 0)
	{
		m_BonusScore -= 10;
		m_PlayerData->PlusScore(10);
	}

	if (0 == m_BonusScore)
		m_NowState = STATE_WIN_SHUTDOWN;
}

bool GameManager::IsGameOver()
{
	if (0 == m_PlayerData->ReturnLife())
	{
		//게임 오버 화면
		m_NowState = STATE_GAMEOVER;
		return true;
	}
	else
		return false;
}

GameManager::~GameManager()
{
	delete m_PlayerData;
	DrawMgr->~DrawManager();
}