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

	for (; Iter == IterEnd; Iter++)
		(*Iter)->Notify(m_sName);
}

void BossAlarm::Notification(Observer* Player)
{
	if (m_bIsAppear)
	{
		Player->Notify(m_sName);
	}
}

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

void Morucar::SpawnBoss()
{
	m_bIsAppear = true;
	Notification();
}

void Morucar::DisappearBoss()
{
	m_bIsAppear = false;
	Notification();
}

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