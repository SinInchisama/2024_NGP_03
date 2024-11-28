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

	// Game Start?

	// while(1) {
	// 
	// recv() // playerInput을 받는 곳
	//
	// Insert_Event_Queue;
	//
	// is game end?
	// }


	while (1) {

		// 데이터 받기
		// 클라이언트로부터 PlayerInput 구조체 정보를 받음. 
		// 
		//typedef struct playerInput {
		//	byte p_index; // - 플레이어 1인지 2인지 구분(1 or 2)
		//	byte input_key; // - 1 ~ 7 입력된 키 정보
		//} playerInput;

		retval = recv(client_sock[i], buf, sizeof(buf), 0);
		if (retval == 0)
			continue;
		buf[retval] = '\0';

		playerInput pInput;
		char* pos = buf;
		const char inputSize = sizeof(playerInput);

		for (int i = 0; i < retval; i += inputSize) {
			memcpy(&pInput, pos, inputSize);

			// pInput에 플레이어 정보, 플레이어의 키 입력값이 들어 있음. 
			// pInput의 정보를 바탕으로 적절한 값 수정
			// 이 루프는 recv한 값을 전부 pInput에 순차적으로 복사한 후 종료됨. 
			
			// 읽어들인 값의 크기를 확인하지 않고 2바이트 단위로 끊어 읽어서 문제가 생길 수도 있겠지만, 
			// 보내는 쪽(클라이언트)의 데이터가 끊겨서 오지 않는 이상 문제될 건 없어보임.  - 안현우

			pos = pos + 2;
		}

		// std::ofstream file(buf, std::ios::binary); // 필요 없는 코드? 
		// std::cout << buf << std::endl;
	}
	// 소켓 닫기
	closesocket(client_sock[i]);

	printf("\n[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr[i].sin_port));

	return 0;
}