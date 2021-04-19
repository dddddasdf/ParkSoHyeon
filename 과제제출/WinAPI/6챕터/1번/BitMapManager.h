#pragma once
#include "BitMap.h"
#include <vector>

class BitMapManager
{
private:
	std::vector <BitMap*> m_BitMapVector;	//��Ʈ�ʵ� �ִ´�
	HDC m_hdc;
	HDC m_MemDC;
	HINSTANCE m_hInst;

public:
	BitMapManager(HDC hdc, HINSTANCE g_hInst);
	bool LoadNewImage(std::string FileName);
	void PrintBitMap(int BitMapNumber, int xLocation, int yLocation);

//	void IsMemDCEmpty();	//MemDC �����
	void DeleteBitMapVector();	//�����Ҵ� ����
};

/*
������ �ϴ� �Լ�
��Ʈ���� ����
��Ʈ�ʿ��� ���̵� �Ѱ��ֱ�->define���� ���� ��¼�� sprintf �ӽñ� ���ñ� �� �ϼ�
��Ʈ�� �ı�
��Ÿ �յ�

*/