#include "BitMapManager.h"

BitMapManager::BitMapManager(HDC hdc, HINSTANCE g_hInst) : m_hInst(g_hInst)
{

}

bool BitMapManager::LoadNewImage(std::string FileName)
{
	BitMap *NewBitMap = new BitMap(FileName);

	if (NewBitMap->ReturnBitMap() != NULL)
	{
		m_BitMapVector.push_back(NewBitMap);
		return true;
	}
	else
	{
		return false;
	}
}

void BitMapManager::PrintBitMap(HDC hdc, int BitMapNumber, int xLocation, int yLocation)
{
	HBITMAP OldBitMap;
	HBITMAP BitMapTmp;
	//BITMAP BitMapSize;	//���� ũ�� ���ϴ� ��
	HDC MemDC = CreateCompatibleDC(hdc);
	//int PictureSizeX, PictureSizeY;	//���� ũ�� ������ ����

	BitMapTmp = m_BitMapVector[BitMapNumber]->ReturnBitMap();
	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMapTmp);

	//���� ũ�� ���ϴ� ��Ʈ
	/*GetObject(BitMapTmp, sizeof(BITMAP), &BitMapSize);
	PictureSizeX = BitMapSize.bmWidth;
	PictureSizeY = BitMapSize.bmHeight;*/
	//���� ũ�� ���ϴ� ��Ʈ ����-�̹� �� �� �� �ʹ� �������� �� ���Ƽ�...

	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMap);

	DeleteObject(BitMapTmp);
	DeleteDC(MemDC);
}