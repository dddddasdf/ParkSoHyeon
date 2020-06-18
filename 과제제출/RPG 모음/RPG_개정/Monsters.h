#pragma once
#include "Headers.h"

struct Monster
{
	string sMonsterName;	//�� �̸�
	int iMonsterCurrentLife;	//�� ���� �����
	int iMonsterMaxLife;	//�� �ִ� �����
	int iMonsterAttack;	//�� ���ݷ�
	int iMonsterDropGold;	//���� �ִ� ���
	int iMonsterLevel;	//�� ���� ����
	int iMonsterCurrentExp;	//�� ���� ����ġ
	int iMonsterMaxExp;	//���� ���� ���� ���� �䱸 ����ġ
	int iMonsterDropExp;	//���� �ִ� ����ġ
	int iMonsterNumber;	//�� ��ȣ
};

struct MonsterNode
{
	Monster MonsterInformation;
	int iMonsterNumber;
	MonsterNode *Next;
};

struct MonsterList
{
	MonsterNode *Head;
	MonsterNode *Current;
	int iMonsterPopulation;
};

class Monsters
{
private:
	int m_iMonsterPopulation;
	MonsterList *NewMonsterList;
public:
	bool InitMonsterData();	//�� ���� �ʱ�ȭ. InitUserInfo()�� �Ȱ��� ��Ŀ����
	string ReturnMonsterName(int MonsterNumber);
	int ReturnMonsterStatus(int MonsterNumber, int StatusType);
	void DeleteMonsterList();
};

