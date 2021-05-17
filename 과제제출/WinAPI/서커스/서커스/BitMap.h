#pragma once
#include "Defines.h"

class BitMap
{
private:
	HBITMAP m_BitMap;

public:
	BitMap();	//나중에 삭제 필요
	BitMap(std::string FileName);

	HBITMAP ReturnBitMap();	//매니저로 비트맵 정보 넘김
};

//단순히 생성자에서 불러올 것이 아니라...
