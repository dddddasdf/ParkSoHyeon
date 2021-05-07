#pragma once
#include <windows.h>
#include <iostream>

class BitMap
{
private:
	HBITMAP m_BitMap;

public:
	BitMap();

	HBITMAP ReturnBitMap();	//매니저로 비트맵 정보 넘김
};

//단순히 생성자에서 불러올 것이 아니라...
