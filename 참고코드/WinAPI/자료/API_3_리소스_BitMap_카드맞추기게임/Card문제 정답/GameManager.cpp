#include "GameManager.h"



GameManager::GameManager()
{

}

void GameManager::Draw(HDC hdc)
{
	for (int i = 0; i < CARDMAX ; i++)
		m_CardList[i].Draw(hdc);
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	m_CardList[0].Init(hdc, hInst, IDB_BITMAP1, "강아지", 100 + (0 * 145) + (0 * 10), 100 + (0 * 235));
	m_CardList[1].Init(hdc, hInst, IDB_BITMAP2, "호랑이", 100 + (1 * 145) + (1 * 10), 100 + (0 * 235));
	m_CardList[2].Init(hdc, hInst, IDB_BITMAP3, "오리", 100 + (2 * 145) + (2 * 10), 100 + (0 * 235));
	m_CardList[3].Init(hdc, hInst, IDB_BITMAP4, "코끼리", 100 + (3 * 145) + (3 * 10), 100 + (0 * 235));
	m_CardList[4].Init(hdc, hInst, IDB_BITMAP5, "소", 100 + (4 * 145) + (4 * 10), 100 + (0 * 235));
	m_CardList[5].Init(hdc, hInst, IDB_BITMAP6, "말", 100 + (0 * 145) + (0 * 10), 100 + (1 * 235));
	m_CardList[6].Init(hdc, hInst, IDB_BITMAP7, "고양이", 100 + (1 * 145) + (1 * 10), 100 + (1 * 235));
	m_CardList[7].Init(hdc, hInst, IDB_BITMAP8, "원숭이", 100 + (2 * 145) + (2 * 10), 100 + (1 * 235));
	m_CardList[8].Init(hdc, hInst, IDB_BITMAP9, "개구리", 100 + (3 * 145) + (3 * 10), 100 + (1 * 235));
	m_CardList[9].Init(hdc, hInst, IDB_BITMAP10, "닭", 100 + (4 * 145) + (4 * 10), 100 + (1 * 235));
	ReleaseDC(hWnd, hdc);
}


void GameManager::ColliderCheck(HWND hWnd, POINT point)
{

	for (int i = 0; i < CARDMAX; i++)
		m_CardList[i].ColliderCheck(hWnd, point);
}

GameManager::~GameManager()
{
}
