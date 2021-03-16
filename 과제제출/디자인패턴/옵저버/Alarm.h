#pragma once
#include "Headers.h"

enum APPEAR
{
	APPEAR_COME,
	APPEAR_AWAY
};

class Observer
{
private:

public:
	virtual void Notify(std::string name, int appear) = 0;
};

//���� ���

class BossAlarm
{
private:
	std::vector <Observer*> SetedPlayerList;
	std::string m_sName;

protected:
	bool m_bIsAppear;

public:
	BossAlarm(std::string Name) : m_sName(Name) { }

	void AddPlayer(Observer* Player);
	void RemovePlayer(Observer* Player);

	void Notification();
	void Notification(Observer* Player);
};

class ClearDragon : public BossAlarm
{
private:

public:
	ClearDragon() : BossAlarm("���� �巡��") { m_bIsAppear = false; }

	void SpawnBoss();
	void DisappearBoss();
};

class Morucar : public BossAlarm
{
private:

public:
	Morucar() : BossAlarm("���ī") { m_bIsAppear = false; }

	void SpawnBoss();
	void DisappearBoss();
};

class Anton : public BossAlarm
{
private:

public:
	Anton() : BossAlarm("����") { m_bIsAppear = false; }

	void SpawnBoss();
	void DisappearBoss();
};

//

class Player : public Observer
{
private:
	std::string m_sPlayerName;
	BossAlarm* SubscribeBossAlarm;
	bool m_bAlarmState;
public:
	Player(std::string name) : m_sPlayerName(name) {  }

	void Notify(std::string name, int appear) override;
	
	void SetBossAlarm(BossAlarm* NewAlarm);
	void GetBossState();
	void TurnOnBossState();
	void TurnOffBossState();
	bool ReturnAlarmState();
};

//class Alarm
//
//{
//};

/*
������ ������� ���� �˸��� ����
*/