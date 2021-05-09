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

	int m_CharacterLocationX;	//ĳ���� ��ġ
	int m_CharacterLocationY;
	int m_CharacterDirection;	//ĳ���� ����
public:
	void Init();
	void Standing(HDC hdc);
	void ChangeNeutral();
	void Moving(HDC hdc, int Direction);
};

#define Chara Character::GetInstance()
