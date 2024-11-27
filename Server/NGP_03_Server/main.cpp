#include "Common.h"
#include "fstream"
#include "iostream"
#include "Windows.h"

#define SERVERPORT 9000
#define BUFSIZE    1024

CRITICAL_SECTION cs;

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID arg)
{
	EnterCriticalSection(&cs);

	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];
	int len; // ���� ���� ������
	float total_received = 0;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	while (1) {

		// ������ �ޱ�
		// Ŭ���̾�Ʈ�� ���ϸ��� ������ �κ�
		retval = recv(client_sock, buf, sizeof(buf), 0);

		buf[retval] = '\0';

		std::ofstream file(buf, std::ios::binary);
		std::cout << buf << std::endl;

		// Ŭ���̾�Ʈ�� ������ ���� ������ �κ�
		// ������ �ޱ�(���� ����)
		/*retval = recv(client_sock, (char*)&len, sizeof(int), MSG_WAITALL);

		while (retval = recv(client_sock, buf, BUFSIZE, MSG_WAITALL)) {
			file.write(buf, retval);
			total_received += (float)retval;
			float progress = total_received / len * 100;
		}*/

		// ���� �ݱ�
		closesocket(client_sock);

		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));


		break;
	}
	return 0;
}


int main(int argc, char* argv[])

{
	int retval;

	// �Ӱ� ���� �ʱ�ȭ
	InitializeCriticalSection(&cs);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
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

	// ������ ��ſ� ����� ����
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

		printf("\n\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// ������ ����
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}
	DeleteCriticalSection(&cs);
	// ���� �ݱ�
	closesocket(listen_sock);
	// ���� ����
	WSACleanup();
	return 0;
}