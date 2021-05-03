#pragma once
#include "BitMap.h"
#include <vector>
#include "TemplateSingleton.h"
#include "Enums.h"


class BitMapManager
{
private:
	HINSTANCE m_hInst;

public:
	BitMapManager(HINSTANCE g_hInst);
	HBITMAP LoadNewImage(std::string FileName);
	void PrintBitMap(HDC hdc, int BitMapNumber, int xLocation, int yLocation);
};

/*
������ �ϴ� �Լ�
��Ʈ���� ����
��Ʈ�ʿ��� ���̵� �Ѱ��ֱ�->define���� ���� ��¼�� sprintf �ӽñ� ���ñ� �� �ϼ�
��Ʈ�� �ı�
��Ÿ �յ�

*/