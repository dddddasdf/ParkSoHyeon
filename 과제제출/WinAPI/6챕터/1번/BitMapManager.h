#pragma once
#include "BitMap.h"
#include <vector>

#define IMAGESIZE_X 145
#define IMAGESIZE_Y 235

enum CARD_LOCATION
{
	CARD_LOCATION_FIRST_X = 20,
	CARD_LOCATION_FIRST_Y = 50,
	CARD_LOCATION_SECOND_X = 180,
	CARD_LOCATION_SECOND_Y = 50,
	CARD_LOCATION_THIRD_X = 340,
	CARD_LOCATION_THIRD_Y = 50,
	CARD_LOCATION_FOURTH_X = 500,
	CARD_LOCATION_FOURTH_Y = 50,
	CARD_LOCATION_FIFTH_X = 660,
	CARD_LOCATION_FIFTH_Y = 50,
	CARD_LOCATION_SIXTH_X = 20,
	CARD_LOCATION_SIXTH_Y = 350,
	CARD_LOCATION_SEVENTH_X = 180,
	CARD_LOCATION_SEVENTH_Y = 350,
	CARD_LOCATION_EIGHTH_X = 340,
	CARD_LOCATION_EIGHTH_Y = 350,
	CARD_LOCATION_NINETH_X = 500,
	CARD_LOCATION_NINETH_Y = 350,
	CARD_LOCATION_TENTH_X = 660,
	CARD_LOCATION_TENTH_Y = 350
};

enum CARD_PICTURE
{
	CARD_PICTURE_BLANK = 0,
	CARD_PICTURE_FIRST = 1,
	CARD_PICTURE_SECOND = 2,
	CARD_PICTURE_THIRD = 3,
	CARD_PICTURE_FOURTH = 4,
	CARD_PICTURE_FIFTH = 5
};

class BitMapManager
{
private:
	std::vector <BitMap*> m_BitMapVector;	//비트맵들 넣는다<-쓸 일이 없어졌다
	HINSTANCE m_hInst;

public:
	BitMapManager(HDC hdc, HINSTANCE g_hInst);
	//bool LoadNewImage, (std::string FileName);	//기존에 쓰던 함수. 지금은 안 쓰고 아랫걸로 대체
	HBITMAP LoadNewImage(std::string FileName);
	void PrintBitMap(HDC hdc, int BitMapNumber, int xLocation, int yLocation);

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