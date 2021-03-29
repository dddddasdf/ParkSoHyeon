#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C4No1");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static bool IsBottom = false;
	static bool IsUp = false;
	static bool IsLeft = false;

	static int x = 320;
	static int y = 320;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 20, 20, 620, 620);
		Ellipse(hdc, x - 30, y - 30, x + 30, y + 30);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
	{
		if (!IsBottom)
		{
			y += 10;

			if (y + 30 == 620)
			{
				IsBottom = true;
				IsUp = true;
			}
		}
		else
		{
			if (IsUp == true && IsLeft == true)
			{
				x -= 10;
				y -= 10;
			}
			else if (IsUp == false && IsLeft == true)
			{
				x -= 10;
				y += 10;
			}
			else if (IsUp == true && IsLeft == false)
			{
				x += 10;
				y -= 10;
			}
			else if (IsUp == false && IsLeft == false)
			{
				x += 10;
				y += 10;
			}

			if (x == 590)
				IsLeft = true;

			if (x == 50)
				IsLeft = false;

			if (y == 590)
				IsUp = true;

			if (y == 50)
				IsUp = false;
		}
	}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}