#pragma once
#include "Defines.h"

class BitMap
{
private:
	HBITMAP m_BitMap;

	int m_SizeWidth;
	int m_SizeHeight;

public:
	BitMap();	//���߿� ���� �ʿ�
	BitMap(std::string FileName);

	HBITMAP ReturnBitMap();	//��Ʈ�� ���� �ѱ�

	int ReturnBitMapWidth() { return m_SizeWidth; }
	int ReturnBitMapHeight() { return m_SizeHeight; }
};

//�ܼ��� �����ڿ��� �ҷ��� ���� �ƴ϶�...
