#pragma once
#include "TemplateSingleton.h"
#include "BitMapManager.h"
#include "Definition.h"
#include <windows.h>


class Character : public Singleton <Character>
{
private:
	bool m_IsLeftLeg;	//�޹� ������ ����: true�� �� �޹�, false�� �� ������. Ű �Է��� �����Ǿ �̵��� ������ true false �����ư��� ��ȯ�ȴ�.
	bool m_IsNeutralFirst;	//�߸��� �� �����⸦ ǥ���ϱ� ����

	int m_CharacterLocationX;	//ĳ���� X��ġ
	int m_CharacterLocationY;	//ĳ���� Y��ġ
	int m_CharacterDirection;	//ĳ���� ����
	int m_CharacterGesture;	//ĳ������ ���� ����

	
public:
	void Init();

	void Moving(int Direction);	//ĳ���� �̵��� ���� ĳ���Ͱ� ������ �ִ� ��������� �����Ű�� �Լ� Ű�Է��� �����Ǹ� �����Լ����� ȣ���Ѵ�
	void PrintCharacter(HDC *hdc);	//ĳ���� ��������Ʈ ���
};

#define Chara Character::GetInstance()

/*
ĳ���� ���� �ٲٴ� �Ŷ� ����̶� �и��ϴ� �� ���� �� �ϴ�


*/
