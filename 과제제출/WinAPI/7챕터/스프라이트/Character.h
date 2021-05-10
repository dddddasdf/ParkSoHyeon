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

	int m_CharacterLocationX;	//캐릭터 X위치
	int m_CharacterLocationY;	//캐릭터 Y위치
	int m_CharacterDirection;	//캐릭터 방향
	int m_CharacterGesture;	//캐릭터의 현재 상태

	
public:
	void Init();

	void Moving(int Direction);	//캐릭터 이동을 위해 캐릭터가 가지고 있는 멤버변수들 변경시키는 함수 키입력이 감지되면 메인함수에서 호출한다
	void PrintCharacter(HDC *hdc);	//캐릭터 스프라이트 출력
};

#define Chara Character::GetInstance()

/*
캐릭터 방향 바꾸는 거랑 출력이랑 분리하는 게 좋을 듯 하다


*/
