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

	// Game Start?

	// while(1) {
	// 
	// recv() // playerInput�� �޴� ��
	//
	// Insert_Event_Queue;
	//
	// is game end?
	// }


	while (1) {

		// ������ �ޱ�
		// Ŭ���̾�Ʈ�κ��� PlayerInput ����ü ������ ����. 
		// 
		//typedef struct playerInput {
		//	byte p_index; // - �÷��̾� 1���� 2���� ����(1 or 2)
		//	byte input_key; // - 1 ~ 7 �Էµ� Ű ����
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

			// pInput�� �÷��̾� ����, �÷��̾��� Ű �Է°��� ��� ����. 
			// pInput�� ������ �������� ������ �� ����
			// �� ������ recv�� ���� ���� pInput�� ���������� ������ �� �����. 
			
			// �о���� ���� ũ�⸦ Ȯ������ �ʰ� 2����Ʈ ������ ���� �о ������ ���� ���� �ְ�����, 
			// ������ ��(Ŭ���̾�Ʈ)�� �����Ͱ� ���ܼ� ���� �ʴ� �̻� ������ �� �����.  - ������

			pos = pos + 2;
		}

		// std::ofstream file(buf, std::ios::binary); // �ʿ� ���� �ڵ�? 
		// std::cout << buf << std::endl;
	}
	// ���� �ݱ�
	closesocket(client_sock[i]);

	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr[i].sin_port));

	return 0;
}