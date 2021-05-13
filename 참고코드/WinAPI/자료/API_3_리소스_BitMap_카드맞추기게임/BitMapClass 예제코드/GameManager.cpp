#include "GameManager.h"



GameManager::GameManager()
{

}

void GameManager::Draw(HDC hdc, int x, int y)
{
	m_BitMap.Draw(hdc, x/2, y/2,5,5);
	m_BitMap2.Draw(hdc, x * 3, y * 3,2,2);
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	m_BitMap.Init(hdc, hInst,IDB_BITMAP1);
	m_BitMap2.Init(hdc, hInst, IDB_BITMAP2);
	ReleaseDC(hWnd, hdc);
}

GameManager::~GameManager()
{
}
