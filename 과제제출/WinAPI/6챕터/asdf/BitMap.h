#pragma once
#include <windows.h>
#include <iostream>

class BitMap
{
private:
	HBITMAP m_BitMap;

public:
	BitMap(std::string FileName);

	HBITMAP ReturnBitMap();	//�Ŵ����� ��Ʈ�� ���� �ѱ�
};

//�ܼ��� �����ڿ��� �ҷ��� ���� �ƴ϶�...
