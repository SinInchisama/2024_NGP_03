#include "RecvThead.h"

extern Player players[2];

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI RecvThread(LPVOID arg)
{
	int retval;
	int i = index;
	client_sock[i] = (SOCKET)arg;
	char addr[INET_ADDRSTRLEN];
	int addrlen;

	char buffer[2] = { 0 };
	int len; // ���� ���� ������
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

		recv(client_sock[i], buffer, sizeof(buffer), 0);
		EnterCriticalSection(&cs);
		playerInput input = playerInput::deserialize(buffer);
		players[input.p_index].Set_Action(input.input_key);
		LeaveCriticalSection(&cs);
		// ������ �ޱ�
		// Ŭ���̾�Ʈ�κ��� PlayerInput ����ü ������ ����. 
		// 
		//typedef struct playerInput {
		//	byte p_index; // - �÷��̾� 1���� 2���� ����(1 or 2)
		//	byte input_key; // - 1 ~ 7 �Էµ� Ű ����
		//} playerInput;
		//recv(client_sock[i], &cbuffer, sizeof(cbuffer), 0);

		/*retval = recv(client_sock[i], buf, sizeof(buf), 0);
		if (retval == 0)
			continue;
		buf[retval] = '\0';

		playerInput pInput;
		char* pos = buf;
		const char inputSize = sizeof(playerInput);*/

		//for (int i = 0; i < retval; i += inputSize) {
		//	memcpy(&pInput, pos, inputSize);

		//	// pInput�� �÷��̾� ����, �÷��̾��� Ű �Է°��� ��� ����. 
		//	// pInput�� ������ �������� ������ �� ����
		//	// �� ������ recv�� ���� ���� pInput�� ���������� ������ �� �����. 
		//	
		//	// �о���� ���� ũ�⸦ Ȯ������ �ʰ� 2����Ʈ ������ ���� �о ������ ���� ���� �ְ�����, 
		//	// ������ ��(Ŭ���̾�Ʈ)�� �����Ͱ� ���ܼ� ���� �ʴ� �̻� ������ �� �����.  - ������

		//	pos = pos + 2;
		//}

		// std::ofstream file(buf, std::ios::binary); // �ʿ� ���� �ڵ�? 
		// std::cout << buf << std::endl;
	}
	// ���� �ݱ�
	closesocket(client_sock[i]);

	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr[i].sin_port));

	return 0;
}