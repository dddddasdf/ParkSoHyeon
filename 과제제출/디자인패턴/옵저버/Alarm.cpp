#include "Alarm.h"



//보스 클래스들

void BossAlarm::AddPlayer(Observer* Player)
{
	SetedPlayerList.push_back(Player);
}

void BossAlarm::RemovePlayer(Observer* Player)
{
	std::vector <Observer*>::iterator Seek = find(SetedPlayerList.begin(), SetedPlayerList.end(), Player);
	SetedPlayerList.erase(Seek);
}

void BossAlarm::Notification()
{
	std::vector <Observer*>::iterator Iter = SetedPlayerList.begin();
	std::vector <Observer*>::iterator IterEnd = SetedPlayerList.end();

	if (m_bIsAppear)
	{
		for (; Iter < IterEnd; Iter++)
			(*Iter)->Notify(m_sName, m_bIsAppear);
	}
	else
	{
		for (; Iter < IterEnd; Iter++)
			(*Iter)->Notify(m_sName, m_bIsAppear);
	}
}

void BossAlarm::Notification(Observer* Player)
{
	if (m_bIsAppear)
	{
		Player->Notify(m_sName, APPEAR_COME);
	}
	else
	{
		Player->Notify(m_sName, APPEAR_AWAY);
	}
}

//투드
void ClearDragon::SpawnBoss()
{
	m_bIsAppear = true;
	Notification();
}

void ClearDragon::DisappearBoss()
{
	m_bIsAppear = false;
	Notification();
}


//모루카
void Molucar::SpawnBoss()
{
	m_bIsAppear = true;
	Notification();
}

void Molucar::DisappearBoss()
{
	m_bIsAppear = false;
	Notification();
}


//안톤
void Anton::SpawnBoss()
{
	m_bIsAppear = true;
	Notification();
}

void Anton::DisappearBoss()
{
	m_bIsAppear = false;
	Notification();
}


//
void Player::Notify(std::string name, int appear)
{
	gotoxy(0, 23);
	if (m_bAlarmState)
	{
		if (appear == true)
			std::cout << name << " 출현 중\n";
		else
			std::cout << name << " 퇴근 중\n";
	}
	
}

void Player::SetBossAlarm(BossAlarm* NewAlarm)
{
	SubscribeBossAlarm = NewAlarm;
	m_bAlarmState = true;

	SubscribeBossAlarm->AddPlayer(this);
}

void Player::GetBossState()
{
	m_bAlarmState = true;
	SubscribeBossAlarm->Notification(this);
}

void Player::TurnOffBossState()
{
	m_bAlarmState = false;
}

bool Player::ReturnAlarmState()
{
	return m_bAlarmState;
}