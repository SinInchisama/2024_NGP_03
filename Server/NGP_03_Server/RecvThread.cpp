#include "RecvThead.h"

// 클라이언트와 데이터 통신
DWORD WINAPI RecvThread(LPVOID arg)
{
	int retval;
	int i = index;
	client_sock[i] = (SOCKET)arg;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];
	int len; // 고정 길이 데이터
	float total_received = 0;
	++index;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr[i]);
	getpeername(client_sock[i], (struct sockaddr*)&clientaddr[i], &addrlen);
	inet_ntop(AF_INET, &clientaddr[i].sin_addr, addr, sizeof(addr));

	while (1) {

		// 데이터 받기
		// 클라이언트가 파일명을 보내는 부분
		retval = recv(client_sock[i], buf, sizeof(buf), 0);

		buf[retval] = '\0';

		std::ofstream file(buf, std::ios::binary);
		std::cout << buf << std::endl;
	}
	// 소켓 닫기
	closesocket(client_sock[i]);

	printf("\n[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr[i].sin_port));

	return 0;
}