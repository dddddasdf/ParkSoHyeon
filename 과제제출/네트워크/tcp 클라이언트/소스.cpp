#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_BUFFER_SIZE 256
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

void err_quit(const char* msg);

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;
	MessageBox(NULL, "윈속 사용 준비", "윈속 사용 준비 완료.", MB_OK);

	//SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	//if (INVALID_SOCKET == listen_socket)
	//	err_quit("socket");

	//SOCKADDR_IN serveraddr;
	//ZeroMemory(&serveraddr, sizeof(serveraddr));
	//serveraddr.sin_family = AF_INET;
	//serveraddr.sin_port = htons(9000);	//9000번대 포트는 거의 안 쓰기 때문에 예제용으로 많이 쓴다 햇음,,
	//serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sock)
		return -1;

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);	//9000번대 포트는 거의 안 쓰기 때문에 예제용으로 많이 쓴다 햇음,,
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (SOCKET_ERROR == connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)))
		err_quit("connect");

	int len, retval;
	char buf[MAX_BUFFER_SIZE + 1];
	while (1)
	{
		ZeroMemory(buf, sizeof(buf));
		printf("\n[보낼 데이터]");
		if (fgets(buf, MAX_BUFFER_SIZE, stdin) == NULL)
			break;

		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';

		if (strlen(buf) == 0)
			break;

		retval = send(sock, buf, sizeof(buf), 0);
		if (SOCKET_ERROR == retval)
			break;

		printf("[TCP 클라이언트] %d바이트를 보냈습니다.", retval);

		ZeroMemory(buf, sizeof(buf));
		retval = recv(sock, buf, sizeof(buf), 0);
		if (SOCKET_ERROR == retval)
			break;
		else if (0 == retval)
			break;
		
		buf[retval - 1] = '\0';
		printf("[TCP 클라이언트] %d바이트를 받았습니다.", retval);

		printf("\n[받은 데이터]%s \n", buf);
	}

	closesocket(sock);

	WSACleanup();
}

void err_quit(const char* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&IpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCSTR)IpMsgBuf, msg, MB_ICONERROR);

	LocalFree(IpMsgBuf);

	exit(-1);
}

void err_display(const char* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&IpMsgBuf, 0, NULL);

	printf("[%s] %s\n", msg, (LPCSTR)IpMsgBuf);

	LocalFree(IpMsgBuf);
}