#pragma once
#include "Defines.h"

class BitMap
{
private:
	HBITMAP m_BitMap;

public:
	BitMap();	//���߿� ���� �ʿ�
	BitMap(std::string FileName);

	HBITMAP ReturnBitMap();	//�Ŵ����� ��Ʈ�� ���� �ѱ�
};

//�ܼ��� �����ڿ��� �ҷ��� ���� �ƴ϶�...
