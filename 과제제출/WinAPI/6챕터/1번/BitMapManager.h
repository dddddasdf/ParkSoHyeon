#pragma once
#include "BitMap.h"
#include <vector>

class BitMapManager
{
private:
	std::vector <BitMap*> m_BitMapVector;	//비트맵들 넣는다
	HDC m_hdc;
	HDC m_MemDC;
	HINSTANCE m_hInst;

public:
	BitMapManager(HDC hdc, HINSTANCE g_hInst);
	bool LoadNewImage(std::string FileName);
	void PrintBitMap(int BitMapNumber, int xLocation, int yLocation);

//	void IsMemDCEmpty();	//MemDC 지우기
	void DeleteBitMapVector();	//동적할당 해제
};

/*
만들어야 하는 함수
비트맵의 생성
비트맵에게 아이디 넘겨주기->define으로 대충 어쩌고 sprintf 머시기 저시기 와 완성
비트맵 파괴
기타 둥둥

*/