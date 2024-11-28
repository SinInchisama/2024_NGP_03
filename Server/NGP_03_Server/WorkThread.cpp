#include "WorkThread.h"

Player players[2] = { {0, {0.0f, 0.0f, 0.0f}},{0, {0.0f, 0.0f, 0.0f}} };
Box All_Box[20][20];
Timer timer(60);

// 클라이언트와 데이터 통신
DWORD WINAPI WorkThread(LPVOID arg)
{
	Reset_Object();
	
	// send(오브젝트);
	Send_Object();

	//previousTime = std::chrono::high_resolution_clock::now();
	timer.resetTimer();

	while (true) {
		Timer_Check();

		// 임계 영역 진입

		// EventQueue::currentInstance->executeAll();

		// 임계 영역 탈출

		// 행렬 변환(플레이어, 총알 움직임)
		players[0].Calculate_Move();

		// 충돌 체크

		// 전송할 패킷리스트 개수 전송(고정크기)

		// for문으로 패킷 보내기
	}
	return 0;
}

void Reset_Object()
{
	Boxinit(20, 20, 20);
	players[0].Set_Plocate(glm::vec3(0,0,0));
	All_Box[0][0].Color= players[0].Get_Color();
}

void Boxinit(int x, int y, int z)
{
	float xScale = (float)10 / x;
	float yScale = (float)10 / y;
	float zScale = (float)10 / z;
	float xlocate = 5 - (xScale / 2);
	float zlocate = 5 - (zScale / 2);

	glm::vec3 bound_scale = { xScale / 2, yScale, zScale / 2 };
	glm::vec3 Blocate;

	int a = 0;
	for (int i = 0; i < z; i = i++, a++) {
		for (int k = 0; k < x; k++) {
			//All_Box[i][k].Bcolor = glm::vec3{ 0.0f,0.0f ,0.0f };
			Blocate[0] = xlocate - xScale * k;
			Blocate[1] = -yScale;
			Blocate[2] = zlocate - zScale * a;

			All_Box[i][k].Bounding_box[0] = { (Blocate - bound_scale), 1.f };
			All_Box[i][k].Bounding_box[1] = { (Blocate + bound_scale), 1.f };

			glm::mat4 TR = glm::mat4(1.0f);
			glm::mat4 Tx = glm::mat4(1.0f);
			glm::mat4 Scale = glm::mat4(1.0f);

			Scale = glm::scale(Scale, glm::vec3(xScale,yScale,zScale)); //		각 사각형 크기 
			Tx = glm::translate(Tx, Blocate);

			All_Box[i][k].TR = Tx * Scale * TR;
			All_Box[i][k].Color;
		}
	}
}

void Send_Object()
{
	char pbuffer[sizeof(Player)];
	players[0].serializePlayer(pbuffer);
	int result = send(client_sock[1], pbuffer, sizeof(pbuffer), 0);

	char bbuffer[sizeof(Box)];
	for (int i = 0; i < 20; ++i) {
		for (int k = 0; k < 20; k++) {
			All_Box[i][k].serializeBox(bbuffer);
			send(client_sock[1], bbuffer, sizeof(bbuffer), 0);
		}
	}
}

void Timer_Check()
{
	time_t currentTime = time(NULL);
	timer.setDeltaTime(static_cast<float>(currentTime - timer.getPreviousTime())); // 프레임 계산
	timer.setPreviousTime(currentTime);

	if ((currentTime - timer.getStartTime()) % 5)			// 아이템 생성 이벤트
	{
		// 아이템 생성
	}

	if (timer.isFinished())
	{
		// 게임 끝내는 이벤트 생성
	}
}