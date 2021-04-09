#pragma once
#include "resource.h"
#include <windows.h>
#include <iostream>

class BitBitMap
{
private:
	HBITMAP m_MyBitMap;
	HDC m_MemDC;

	int m_BitMapID;
public:
	BitBitMap() { }
	BitBitMap(int BitMapID);
	~BitBitMap();

	void PaintPicture(HINSTANCE gInst, HDC hdc);	//그림그림<-폐기

	void GetBitmapID(int BitMapID);	//비트맵 ID 넘겨 받기인데 이게 int 형으로 되네->기본적으로 생성자에서도 ID 받게끔 했으니 이 함수는 ID를 변경할 필요가 있을 때만

	void Draw(HINSTANCE gInst, HDC hdc);	//기본
	void Draw(HINSTANCE gInst, HDC hdc, int xCoordinate, int yCoordinate);	//좌표만 받은 형태
	void Draw(HINSTANCE gInst, HDC hdc, int xSize, int ySize, int xCoordinate, int yCoordinate);	//크기, 좌표 받은 형태

	void DeleteMyObject() { DeleteObject(m_MyBitMap); }
	void DeleteMyDC() { DeleteObject(m_MyBitMap); }

	void IsEmpty();
};

//디자인패턴이랑 자료구조를 어떻게 쓰란 거지,,,

 /*
 1. 본 cpp로부터 크기를 전달 받고 그에 상응하는 크기로 출력할 것
 2. 비트맵도 원하는 그림을 본 함수가 정할 수 있게 할 것...
 3. 본 함수로부터 받는 매개변수가 너무 많지 않나?->Begin/EndPaint는 본함수에서 해도 될 거 같음


 하나의 객체당 그림 하나를 배정해줄지, 객체 하나로 매번 ID를 바꿔가며 그림을 출력할지가 문제
->객체 지향의 의미를 생각하면 객체 하나에 그림 하나가 맞을 듯

mybitmap 삭제하는 걸 다른 함수로 빼기,,,
draw는 출력만 해야 한다 출력만


DC 관련...
1. 함수를 만들면서 DC를 받아서 미리 memdc에 박을 건지
2. Draw 함수 호출될 때마다 DC 받고 지워버리고 할지...

근데 전자가 낫지 않을까요?
 */

