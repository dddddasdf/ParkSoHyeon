#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("HelloWrld"); //창이름

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//이 함수가 main 역할이다...
	
	HWND hWnd;	//이벤트가 발생한 윈도우를 위한 식별자
	MSG Message;	//이벤트 구분을 위한 식별자
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체다. 맴버변수는 밑에와 같다.
	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 모양
	WndClass.hInstance = hInstance;//(프로그램 핸들값(번호)등록)
	WndClass.lpfnWndProc = WndProc;	//프로세스 함수 호출
	WndClass.lpszClassName = lpszClass;	//클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우의 수직과 수평이 변경 시 다시 그린다.
	RegisterClass(&WndClass);  //만들어진 WidClass를 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);	//화면 출력

	while (GetMessage(&Message, NULL, 0, 0))//사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지 받을 시 종료)->메시지 루프 메시지 큐에서 메시지를 읽어들이고 WM_QUIT는 false고 그 외는 true이다
	{
		TranslateMessage(&Message); //  키보드 입력 메시지 처리함수
		DispatchMessage(&Message); //받은 메시지를 WndProc에 전달하는 함수 전달되는 함수를 체크하여 프로그램은 다음 동작 결정
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//윈도우 프로시저 정의
	//메시지 처리 함수
	//운영체제에 의해 미리 호출되는 callback 함수
	//메시지가 발생할 때 프로그램의 반응 처리
	//어떤 종류의 메시지인지 파악해야 함
	switch (iMessage)
	{
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.<-이거 존나 중요한 거 아니냐
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}

/*
1. 코드 실행
2. window.h 인클루드
3. 이벤트가 발생할 윈도우 식별자와 클래스 정의
4. 클래스의 내부 요소들 정의. 위 코드에서는 배경색은 흰색, 커서는 윈도우 기본 마우스 커서, 아이콘은 없음, 기타 등등
5. 만들어진 윈도우 클래스를 등록하고 해당 윈도우 식별자의 요소들을 집어넣고 윈도우 생성
6. 생성된 윈도우 출력

처음 시작할때 매개변수들은 어디에서 왔는가?
HINSTANCE g_hInst<-이거 전역변수임?
http://elearning.kocw.net/document/WindowPrograming.pdf
https://hellowoori.tistory.com/9
*/