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

	void PaintPicture(HINSTANCE gInst, HDC hdc);	//�׸��׸�<-���

	void GetBitmapID(int BitMapID);	//��Ʈ�� ID �Ѱ� �ޱ��ε� �̰� int ������ �ǳ�->�⺻������ �����ڿ����� ID �ްԲ� ������ �� �Լ��� ID�� ������ �ʿ䰡 ���� ����

	void Draw(HINSTANCE gInst, HDC hdc);	//�⺻
	void Draw(HINSTANCE gInst, HDC hdc, int xCoordinate, int yCoordinate);	//��ǥ�� ���� ����
	void Draw(HINSTANCE gInst, HDC hdc, int xSize, int ySize, int xCoordinate, int yCoordinate);	//ũ��, ��ǥ ���� ����

	void DeleteMyObject() { DeleteObject(m_MyBitMap); }
	void DeleteMyDC() { DeleteObject(m_MyBitMap); }

	void IsEmpty();
};

//�����������̶� �ڷᱸ���� ��� ���� ����,,,

 /*
 1. �� cpp�κ��� ũ�⸦ ���� �ް� �׿� �����ϴ� ũ��� ����� ��
 2. ��Ʈ�ʵ� ���ϴ� �׸��� �� �Լ��� ���� �� �ְ� �� ��...
 3. �� �Լ��κ��� �޴� �Ű������� �ʹ� ���� �ʳ�?->Begin/EndPaint�� ���Լ����� �ص� �� �� ����


 �ϳ��� ��ü�� �׸� �ϳ��� ����������, ��ü �ϳ��� �Ź� ID�� �ٲ㰡�� �׸��� ��������� ����
->��ü ������ �ǹ̸� �����ϸ� ��ü �ϳ��� �׸� �ϳ��� ���� ��

mybitmap �����ϴ� �� �ٸ� �Լ��� ����,,,
draw�� ��¸� �ؾ� �Ѵ� ��¸�


DC ����...
1. �Լ��� ����鼭 DC�� �޾Ƽ� �̸� memdc�� ���� ����
2. Draw �Լ� ȣ��� ������ DC �ް� ���������� ����...

�ٵ� ���ڰ� ���� �������?
 */

