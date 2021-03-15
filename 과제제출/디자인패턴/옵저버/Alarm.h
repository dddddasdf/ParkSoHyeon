#pragma once
#include "Headers.h"

class Observer
{
private:

public:
	virtual void Notify(std::string name) = 0;
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

public:
	void Notify(std::string name) override;
};

//class Alarm
//
//{
//};

