#pragma once
#include "TemplateSingleton.h"
#include "BitMapManager.h"
#include "Definition.h"
#include <windows.h>


class Character : public Singleton <Character>
{
private:
	bool m_IsLeftLeg;	//왼발 오른발 구별: true일 때 왼발, false일 때 오른발. 키 입력이 감지되어서 이동할 때마다 true false 번갈아가며 변환된다.
	bool m_IsNeutralFirst;	//중립일 때 숨쉬기를 표현하기 위함

	int m_CharacterLocationX;	//캐릭터 위치
	int m_CharacterLocationY;
	int m_CharacterDirection;	//캐릭터 방향
public:
	void Init();
	void Standing(HDC hdc);
	void ChangeNeutral();
	void Moving(HDC hdc, int Direction);
};

#define Chara Character::GetInstance()
