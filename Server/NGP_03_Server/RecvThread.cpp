#include "RecvThead.h"

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI RecvThread(LPVOID arg)
{
	int retval;
	int i = index;
	client_sock[i] = (SOCKET)arg;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];
	int len; // ���� ���� ������
	float total_received = 0;
	++index;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr[i]);
	getpeername(client_sock[i], (struct sockaddr*)&clientaddr[i], &addrlen);
	inet_ntop(AF_INET, &clientaddr[i].sin_addr, addr, sizeof(addr));

	while (1) {

		// ������ �ޱ�
		// Ŭ���̾�Ʈ�� ���ϸ��� ������ �κ�
		retval = recv(client_sock[i], buf, sizeof(buf), 0);

		buf[retval] = '\0';

		std::ofstream file(buf, std::ios::binary);
		std::cout << buf << std::endl;
	}
	// ���� �ݱ�
	closesocket(client_sock[i]);

	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr[i].sin_port));

	return 0;
}