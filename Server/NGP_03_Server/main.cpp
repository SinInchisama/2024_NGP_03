#include "Common.h"
#include "fstream"
#include "iostream"
#include "Windows.h"

#define SERVERPORT 9000
#define BUFSIZE    1024

CRITICAL_SECTION cs;

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
	EnterCriticalSection(&cs);

	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];
	int len; // 고정 길이 데이터
	float total_received = 0;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	while (1) {

		// 데이터 받기
		// 클라이언트가 파일명을 보내는 부분
		retval = recv(client_sock, buf, sizeof(buf), 0);

		buf[retval] = '\0';

		std::ofstream file(buf, std::ios::binary);
		std::cout << buf << std::endl;

		// 클라이언트가 동영상 파일 보내는 부분
		// 데이터 받기(고정 길이)
		/*retval = recv(client_sock, (char*)&len, sizeof(int), MSG_WAITALL);

		while (retval = recv(client_sock, buf, BUFSIZE, MSG_WAITALL)) {
			file.write(buf, retval);
			total_received += (float)retval;
			float progress = total_received / len * 100;
		}*/

		// 소켓 닫기
		closesocket(client_sock);

		printf("\n[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));


		break;
	}
	return 0;
}


int main(int argc, char* argv[])

{
	int retval;

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
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

		printf("\n\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 스레드 생성
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}
	DeleteCriticalSection(&cs);
	// 소켓 닫기
	closesocket(listen_sock);
	// 윈속 종료
	WSACleanup();
	return 0;
}