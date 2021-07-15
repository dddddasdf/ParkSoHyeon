#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_BUFFER_SIZE 256
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

void err_quit(const char* msg);
DWORD WINAPI ProcessClient(LPVOID arg);

std::vector <SOCKET> g_SocketVector;
HANDLE g_hMutex;

#pragma pack(1)
struct TEST
{
	char Buffer[256];
};
#pragma pack()

int main()
{
	g_hMutex = CreateMutex(NULL, false, NULL);
	if (NULL == g_hMutex)
		return -1;
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(g_hMutex);
		return -1;
	}
	
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

	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == listen_socket)
		return -1;

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);	//9000번대 포트는 거의 안 쓰기 때문에 예제용으로 많이 쓴다 햇음,,
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (bind(listen_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
	{
		closesocket(listen_socket);
		WSACleanup();
		err_quit("bind");
	}

	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(listen_socket);
		WSACleanup();
		err_quit("listen");
	}

	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(SOCKADDR_IN);
	ZeroMemory(&clientaddr, addrlen);

	//SOCKET client_socket;
	//int retval;
	//char buf[MAX_BUFFER_SIZE + 1];

	SOCKET client_socket;
	HANDLE hThread;
	DWORD threadID;

	while (1)
	{
		client_socket = accept(listen_socket, (SOCKADDR*)&clientaddr, &addrlen);
		if (INVALID_SOCKET == client_socket)
			continue;

		printf("\n[TCP 서버]클라이언트 접속: IP 주소 = %s, 포트 번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_socket, 0, &threadID);
		if (NULL == hThread)
			printf("[오류]스레드 생성 실패!\n");
		else
			CloseHandle(hThread);
	}

	/*while (1)
	{
		client_socket = accept(listen_socket, (SOCKADDR*)&clientaddr, &addrlen);
		if (INVALID_SOCKET == client_socket)
			continue;

		printf("[TCP 서버] 클라이언트 접속: IP 주소 = %s, 포트 번호=%d\n.", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		while (1)
		{
			ZeroMemory(buf, sizeof(buf));

			retval = recv(client_socket, buf, sizeof(buf), 0);

			if (SOCKET_ERROR == retval)
				break;
			else if (0 == retval)
				break;

			buf[retval - 1] = '\0';
			printf("\n[TCP/%s: %d] %s \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);

			retval = send(client_socket, buf, retval, 0);
			if (SOCKET_ERROR == retval)
				break;
		}

		closesocket(client_socket);

		printf("[TCP 서버] 클라이언트 종료: IP 주소 = %s, 포트 번호=%d\n.", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}


	closesocket(listen_socket);*/

	CloseHandle(g_hMutex);

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

DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
	int retval;
	char buf[sizeof(TEST)];

	WaitForSingleObject(g_hMutex, INFINITE);
	g_SocketVector.push_back(client_sock);
	ReleaseMutex(g_hMutex);

	while (1)
	{
		ZeroMemory(buf, sizeof(buf));

		retval = recv(client_sock, buf, sizeof(buf), 0);

		if (SOCKET_ERROR == retval)
			break;
		else if (0 == retval)
			break;

		TEST* recv_packet = (TEST*)buf;
		
		printf("\n[TCP/%s: %d] %s \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), recv_packet->Buffer);

		TEST send_packet = *recv_packet;
		WaitForSingleObject(g_hMutex, INFINITE);
		for (const auto& sock : g_SocketVector)
		{
			retval = send(sock, (char*)&send_packet, sizeof(TEST), 0);

			if (SOCKET_ERROR == retval)
				break;
		}

		ReleaseMutex(g_hMutex);
	}

	WaitForSingleObject(g_hMutex, INFINITE);
	auto result = std::find(g_SocketVector.begin(), g_SocketVector.end(), client_sock);
	if (g_SocketVector.end() != result) 
		g_SocketVector.erase(result);
	ReleaseMutex(g_hMutex);

	closesocket(client_sock);

	printf("[TCP 서버] 클라이언트 종료: IP 주소 = %s, 포트 번호=%d\n.", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}