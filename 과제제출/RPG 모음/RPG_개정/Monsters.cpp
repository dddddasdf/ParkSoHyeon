#include "Monsters.h"

bool Monsters::InitMonsterData()
{
	//�� ���� ���ڴ� �����ϴ� ������ �� ��
	//����Ʈ �� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���̸�, ���ݷ�, �����, ���� �ϱ� ���� ����ġ, �ִ� ����ġ, ����, �ִ� ���
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ ��������

	ifstream MonsterInfoLoad;
	MonsterInfoLoad.open("DefaultMonsterInfo.txt");
	if (MonsterInfoLoad.is_open())
	{
		NewMonsterList = new MonsterList;
		MonsterInfoLoad >> NewMonsterList->iMonsterPopulation;

		NewMonsterList->Head = new MonsterNode;
		NewMonsterList->Head->Next = NULL;
		NewMonsterList->Current = NewMonsterList->Head;

		int iMonsterNumberTmp = 1;

		while (!MonsterInfoLoad.eof())
		{
			MonsterNode *NewMonsterNode = new MonsterNode;

			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.sMonsterName;
			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.iMonsterAttack;
			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.iMonsterMaxLife;
			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.iMonsterMaxExp;
			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.iMonsterDropExp;
			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.iMonsterLevel;
			MonsterInfoLoad >> NewMonsterNode->MonsterInformation.iMonsterDropGold;
			NewMonsterNode->MonsterInformation.iMonsterCurrentExp = 0;
			NewMonsterNode->MonsterInformation.iMonsterCurrentLife = NewMonsterNode->MonsterInformation.iMonsterMaxLife;
			NewMonsterNode->MonsterInformation.iMonsterNumber = iMonsterNumberTmp;
			
			NewMonsterNode->Next = NewMonsterList->Current->Next;
			NewMonsterList->Current->Next = NewMonsterNode;
			NewMonsterList->Current = NewMonsterList->Current->Next;	//�̷��� �ϸ� Head ��忡 ���� ��带 ���鼭 �� ������ ��忡 �ű� �����͸� �߰��� �� �ִ�
			iMonsterNumberTmp++;
		}

		NewMonsterList->Current = NewMonsterList->Head;	//Current ��ġ �ʱ�ȭ

		return true;
	}
	else
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
}