#include "WorkThread.h"

Player players[2] = { {0, {0.0f, 0.0f, 0.0f}},{0, {0.0f, 0.0f, 0.0f}} };
Box All_Box[20][20];

// 클라이언트와 데이터 통신
DWORD WINAPI WorkThread(LPVOID arg)
{
	Reset_Object();
	Send_Object();
	
	// send(오브젝트);

	//previousTime = std::chrono::high_resolution_clock::now();

	while (true) {
		Timer_Check();

		// 임계 영역 진입

		// EventQueue::currentInstance->executeAll();

		// 임계 영역 탈출

		// 행렬 변환

		// 충돌 체크

		// 전송할 패킷리스트 개수 전송(고정크기)

		// for문으로 패킷 보내기
	}
	return 0;
}

void Reset_Object()
{
	Boxinit(20, 20, 20);
	players[0].Set_Plocate(All_Box[0][0].Blocate);
	All_Box[0][0].Bcolor = players[0].Get_Color();
}

void Boxinit(int x, int y, int z)
{
	float xScale = (float)10 / x;
	float yScale = (float)10 / y;
	float zScale = (float)10 / z;
	float xlocate = 5 - (xScale / 2);
	float zlocate = 5 - (zScale / 2);

	glm::vec3 bound_scale = { xScale / 2, yScale, zScale / 2 };

	int a = 0;
	for (int i = 0; i < z; i = i++, a++) {
		for (int k = 0; k < x; k++) {
			All_Box[i][k].Bscale[0] = xScale;
			All_Box[i][k].Bscale[1] = yScale;
			All_Box[i][k].Bscale[2] = zScale;
			All_Box[i][k].Bcolor = glm::vec3{ 0.0f,0.0f ,0.0f };
			All_Box[i][k].Blocate[0] = xlocate - xScale * k;
			All_Box[i][k].Blocate[1] = -yScale;
			All_Box[i][k].Blocate[2] = zlocate - zScale * a;

			All_Box[i][k].offset = i * x + k;

			All_Box[i][k].Bounding_box[0] = { (All_Box[i][k].Blocate - bound_scale), 1.f };
			All_Box[i][k].Bounding_box[1] = { (All_Box[i][k].Blocate + bound_scale), 1.f };

			glm::mat4 TR = glm::mat4(1.0f);
			glm::mat4 Tx = glm::mat4(1.0f);
			glm::mat4 Scale = glm::mat4(1.0f);

			Scale = glm::scale(Scale, glm::vec3(All_Box[i][k].Bscale)); //		각 사각형 크기 
			Tx = glm::translate(Tx, All_Box[i][k].Blocate);

			All_Box[i][k].TR = Tx * Scale * TR;
		}

	}
}

void Send_Object() 
{
	char pbuffer[sizeof(Player)];
	players[0].serializePlayer(pbuffer);
	int result = send(client_sock[1], pbuffer, sizeof(pbuffer), 0);
}

void Timer_Check()
{
	//auto currentTime = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<float> deltaTime = currentTime - previousTime;
	//previousTime = currentTime;

	//auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(previousTime.time_since_epoch()).count(); // 경과 시간 (초 단위)

	//if (elapsed % 5)
}