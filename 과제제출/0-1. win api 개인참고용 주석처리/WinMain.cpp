#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("HelloWrld"); //â�̸�

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//�� �Լ��� main �����̴�...
	
	HWND hWnd;	//�̺�Ʈ�� �߻��� �����츦 ���� �ĺ���
	MSG Message;	//�̺�Ʈ ������ ���� �ĺ���
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ���
	WndClass.hInstance = hInstance;//(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc;	//���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass;	//Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass);  //������� WidClass�� ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);	//ȭ�� ���

	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)->�޽��� ���� �޽��� ť���� �޽����� �о���̰� WM_QUIT�� false�� �� �ܴ� true�̴�
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ� ���޵Ǵ� �Լ��� üũ�Ͽ� ���α׷��� ���� ���� ����
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//������ ���ν��� ����
	//�޽��� ó�� �Լ�
	//�ü���� ���� �̸� ȣ��Ǵ� callback �Լ�
	//�޽����� �߻��� �� ���α׷��� ���� ó��
	//� ������ �޽������� �ľ��ؾ� ��
	switch (iMessage)
	{
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.<-�̰� ���� �߿��� �� �ƴϳ�
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}

/*
1. �ڵ� ����
2. window.h ��Ŭ���
3. �̺�Ʈ�� �߻��� ������ �ĺ��ڿ� Ŭ���� ����
4. Ŭ������ ���� ��ҵ� ����. �� �ڵ忡���� ������ ���, Ŀ���� ������ �⺻ ���콺 Ŀ��, �������� ����, ��Ÿ ���
5. ������� ������ Ŭ������ ����ϰ� �ش� ������ �ĺ����� ��ҵ��� ����ְ� ������ ����
6. ������ ������ ���

ó�� �����Ҷ� �Ű��������� ��𿡼� �Դ°�?
HINSTANCE g_hInst<-�̰� ����������?
http://elearning.kocw.net/document/WindowPrograming.pdf
https://hellowoori.tistory.com/9
*/