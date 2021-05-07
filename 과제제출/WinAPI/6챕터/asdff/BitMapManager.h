#pragma once
#include "BitMap.h"
#include <vector>
#include "TemplateSingleton.h"
#include "Enums.h"


class BitMapManager : public Singleton <BitMapManager>
{
private:

public:
	BitMapManager();
	HBITMAP LoadNewImage(std::string FileName);
	void PrintBitMap(HDC hdc, const int& BitMapNumber, const int& xLocation, const int& yLocation);
};

#define BitMapMgr BitMapManager::GetInstance()

/*
������ �ϴ� �Լ�
��Ʈ���� ����
��Ʈ�ʿ��� ���̵� �Ѱ��ֱ�->define���� ���� ��¼�� sprintf �ӽñ� ���ñ� �� �ϼ�
��Ʈ�� �ı�
��Ÿ �յ�

*/