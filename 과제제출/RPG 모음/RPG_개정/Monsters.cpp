#include "Monsters.h"

bool Monsters::InitMonsterData()
{
	//맨 위의 숫자는 등장하는 몬스터의 총 수
	//디폴트 몹 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//몹이름, 공격력, 생명력, 렙업 하기 위한 경험치, 주는 경험치, 레벨, 주는 골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력

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
			NewMonsterList->Current = NewMonsterList->Current->Next;	//이렇게 하면 Head 노드에 더미 노드를 쓰면서 맨 마지막 노드에 신규 데이터를 추가할 수 있다
			iMonsterNumberTmp++;
		}

		NewMonsterList->Current = NewMonsterList->Head;	//Current 위치 초기화

		return true;
	}
	else
		return false;	//디폴트 몬스터 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
}