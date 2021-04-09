#include "BitBitMap.h"

BitBitMap::BitBitMap(int BitMapID) : m_BitMapID(BitMapID)
{

}

void BitBitMap::GetBitmapID(int BitMapID)
{
	m_BitMapID = BitMapID;
}

void BitBitMap::PaintPicture(HINSTANCE gInst, HDC hdc)
{
	HDC MemDC;

	HBITMAP MyBitMap, OldBitMapTmp;

	MemDC = CreateCompatibleDC(hdc);

	MyBitMap = LoadBitmap(gInst, MAKEINTRESOURCE(m_BitMapID));
	OldBitMapTmp = (HBITMAP)SelectObject(MemDC, MyBitMap);

	BitBlt(hdc, 100, 100, 500, 500, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMapTmp);

	DeleteObject(MyBitMap);
	DeleteDC(MemDC);


}

void BitBitMap::Draw(HINSTANCE gInst, HDC hdc)
{
	IsEmpty();

	HBITMAP OldBitMapTmp;
	BITMAP BitMapTmp;

	int PictureSizeX, PictureSizeY;
	//

	m_MemDC = CreateCompatibleDC(hdc);

	m_MyBitMap = LoadBitmap(gInst, MAKEINTRESOURCE(m_BitMapID));
	OldBitMapTmp = (HBITMAP)SelectObject(m_MemDC, m_MyBitMap);
	//

	GetObject(m_MyBitMap, sizeof(BITMAP), &BitMapTmp);
	PictureSizeX = BitMapTmp.bmWidth;
	PictureSizeY = BitMapTmp.bmHeight;

	BitBlt(hdc, 100, 100, PictureSizeX, PictureSizeY, m_MemDC, 0, 0, SRCCOPY);

	SelectObject(m_MemDC, OldBitMapTmp);

	DeleteMyObject();
	DeleteMyDC();
}


void BitBitMap::Draw(HINSTANCE gInst, HDC hdc, int xCoordinate, int yCoordinate)
{
	IsEmpty();

	HBITMAP OldBitMapTmp;
	BITMAP BitMapTmp;

	int PictureSizeX, PictureSizeY;
	//

	m_MemDC = CreateCompatibleDC(hdc);

	m_MyBitMap = LoadBitmap(gInst, MAKEINTRESOURCE(m_BitMapID));
	OldBitMapTmp = (HBITMAP)SelectObject(m_MemDC, m_MyBitMap);
	//

	GetObject(m_MyBitMap, sizeof(BITMAP), &BitMapTmp);
	PictureSizeX = BitMapTmp.bmWidth;
	PictureSizeY = BitMapTmp.bmHeight;

	BitBlt(hdc, xCoordinate, yCoordinate, PictureSizeX, PictureSizeY, m_MemDC, 0, 0, SRCCOPY);

	SelectObject(m_MemDC, OldBitMapTmp);

	DeleteMyObject();
	DeleteMyDC();
}

void BitBitMap::Draw(HINSTANCE gInst, HDC hdc, int xSize, int ySize, int xCoordinate, int yCoordinate)
{
	IsEmpty();

	HBITMAP OldBitMapTmp;
	BITMAP BitMapTmp;

	int PictureSizeX, PictureSizeY;
	//

	m_MemDC = CreateCompatibleDC(hdc);

	m_MyBitMap = LoadBitmap(gInst, MAKEINTRESOURCE(m_BitMapID));
	OldBitMapTmp = (HBITMAP)SelectObject(m_MemDC, m_MyBitMap);
	//

	GetObject(m_MyBitMap, sizeof(BITMAP), &BitMapTmp);
	PictureSizeX = BitMapTmp.bmWidth;
	PictureSizeY = BitMapTmp.bmHeight;

	StretchBlt(hdc, xCoordinate, yCoordinate, xSize, ySize, m_MemDC, 0, 0, PictureSizeX, PictureSizeY, SRCCOPY);

	SelectObject(m_MemDC, OldBitMapTmp);

	DeleteMyObject();
	DeleteMyDC();
}

void BitBitMap::IsEmpty()
{
	if (m_MemDC != NULL)
	{
		DeleteMyDC();
	}

	if (m_MyBitMap != NULL)
	{
		DeleteMyObject();
	}
}

BitBitMap::~BitBitMap()
{
	IsEmpty();
}