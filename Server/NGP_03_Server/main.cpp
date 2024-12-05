#include "Common.h"
#include "fstream"
#include "iostream"
#include "Windows.h"
#include "Public.h"
#include "RecvThead.h"
#include "WorkThread.h"
#include "EventQueue.h"

EventQueue* EventQueue::currentInstance = nullptr;

int main(int argc, char* argv[])
{
	int retval;

	EventQueue eventqueue;  // 전역 변수로 eventqueue 객체 생성
	EventQueue::currentInstance = &eventqueue;

	GameManger gamemanager;

	// 임계 영역 초기화
	InitializeCriticalSection(&cs);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;

	for (int i = 0; i < 2; ++i) {
		// accept()
		addrlen = sizeof(clientaddr);
		sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

		printf("\n\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		client_sock[index++] = sock;
	}

	// 소켓 닫기
	closesocket(listen_sock);


	hThread = CreateThread(NULL, 0, WorkThread,
		(LPVOID)(nullptr), 0, NULL);
	if (hThread == NULL) { 
		std::cerr << "ERROR: hThread is NULL\n"; 
		DeleteCriticalSection(&cs);
		WSACleanup();
		exit(1); 
	}

	WaitForSingleObject(hThread, INFINITE);

	DeleteCriticalSection(&cs);
	WSACleanup();

	return 0;
}