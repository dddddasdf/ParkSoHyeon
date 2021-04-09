#pragma once
#include <windows.h>
#include <iostream>

class BitMap
{
private:
	int m_PictureID;

public:
	bool IDCheck();
};

//단순히 생성자에서 불러올 것이 아니라...
//예외 처리도 필요하다. ID나 파일을 읽어들이지 못했을 경우 해당 파일을 불러오지 못했다는 경고문
