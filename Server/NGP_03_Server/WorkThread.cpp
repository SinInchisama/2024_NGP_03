#include "WorkThread.h"

Box All_Box[20][20];
Timer timer(60);
std::queue<std::unique_ptr<Parent_Packet>> packetQueue;			// packQueue를 유니크 포인트로 만듬.
Item items[20];

// 클라이언트와 데이터 통신
DWORD WINAPI WorkThread(LPVOID arg)
{
	Reset_Object();
	
	// send(오브젝트);
	Send_Object();

	//previousTime = std::chrono::high_resolution_clock::now();
	timer.resetTimer();

	while (true) {
		char cbuffer;
		recv(client_sock[1], &cbuffer, sizeof(cbuffer), 0);
		GameManger::Instance->players[0]->Set_Action(cbuffer);

		Timer_Check();
		

		EventQueue::currentInstance->executeAll(packetQueue);

		

		// 행렬 변환(플레이어, 총알 움직임)
		GameManger::Instance->players[0]->Calculate_Move();

		if (GameManger::Instance->players[0]->Get_Action() & KEY_A) {
			if (!GameManger::Instance->bullets[0]->View) {
				GameManger::Instance->bullets[0]->View = true;
				GameManger::Instance->players[0]->Set_UpAction(KEY_A);

				GameManger::Instance->bullets[0]->InitBullet(0,
					(GameManger::Instance->players[0]->Get_Plocate() + GameManger::Instance->players[0]->Get_Move()), GameManger::Instance->players[0]->Get_Action());
				packetQueue.push(std::make_unique<Create_bullet>(0, true));
			}
		}
		
	if (GameManger::Instance->bullets[0]->View){
		GameManger::Instance->bullets[0]->Move();
		packetQueue.push(std::make_unique<Move_bullet>(0, GameManger::Instance->bullets[0]->Move1));
	}
		

		// 충돌 체크
		glm::mat4 TR1 = glm::mat4(1.0f);
		glm::mat4 Tx = glm::mat4(1.0f);
		Tx = glm::translate(Tx, GameManger::Instance->players[0]->Get_Plocate() + GameManger::Instance->players[0]->Get_Move());
		TR1 = Tx * GameManger::Instance->players[0]->Get_TR();

		glm::vec4 a1 = TR1 * glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f);
		glm::vec4 a2 = TR1* glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);

		glm::vec4 player_bounding_box[2] = { a1, a2 };

		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				if ((player_bounding_box[0][0] <= All_Box[i][j].Bounding_box[1][0] && player_bounding_box[0][0] >= All_Box[i][j].Bounding_box[0][0] && player_bounding_box[0][2] >= All_Box[i][j].Bounding_box[0][2] && player_bounding_box[0][2] <= All_Box[i][j].Bounding_box[1][2]) ||
					(player_bounding_box[0][0] <= All_Box[i][j].Bounding_box[1][0] && player_bounding_box[0][0] >= All_Box[i][j].Bounding_box[0][0] && player_bounding_box[1][2] >= All_Box[i][j].Bounding_box[0][2] && player_bounding_box[1][2] <= All_Box[i][j].Bounding_box[1][2]) ||
					(player_bounding_box[1][0] <= All_Box[i][j].Bounding_box[1][0] && player_bounding_box[1][0] >= All_Box[i][j].Bounding_box[0][0] && player_bounding_box[1][2] >= All_Box[i][j].Bounding_box[0][2] && player_bounding_box[1][2] <= All_Box[i][j].Bounding_box[1][2]) ||
					(player_bounding_box[1][0] <= All_Box[i][j].Bounding_box[1][0] && player_bounding_box[1][0] >= All_Box[i][j].Bounding_box[0][0] && player_bounding_box[0][2] >= All_Box[i][j].Bounding_box[0][2] && player_bounding_box[0][2] <= All_Box[i][j].Bounding_box[1][2]) &&
					(player_bounding_box[0][1] <= All_Box[i][j].Bounding_box[1][1] && player_bounding_box[1][1] >= All_Box[i][j].Bounding_box[0][1])) {
					EventQueue::currentInstance->addEvent(std::bind(&Box::Chage_Color, &All_Box[i][j], GameManger::Instance->players[0]->Get_Color(),i*20 + j,0));
				}
			}
		}

		// 매번 보내야되는 패킷
		packetQueue.push(std::make_unique<Update_score>(GameManger::Instance->players[0]->Get_Box(), GameManger::Instance->players[1]->Get_Box()));
		packetQueue.push(std::make_unique<Move_Packet>(1, GameManger::Instance->players[0]->Get_Move()));

		// 클라이언트로 큐의 크기 전송

		char size_buffer[sizeof(int)];
		int queue_size = packetQueue.size();
		std::memcpy(size_buffer, &queue_size, sizeof(int));
		send(client_sock[1], size_buffer, sizeof(size_buffer), 0);

		// packetQueue가 빌 때까지 소켓데이터를 보냄.
		while (!packetQueue.empty()) {
			char buffer[128];
			std::unique_ptr<Parent_Packet> packet = std::move(packetQueue.front());
			packetQueue.pop();
			// 패킷 직렬화
			packet->serialize(buffer);
			send(client_sock[1], buffer, sizeof(buffer), 0);
		}
	}
	return 0;
}

void Reset_Object()
{
	Boxinit(20, 20, 20);
	GameManger::Instance->players[0]->Set_Plocate(glm::vec3(0,0,0));
	All_Box[0][0].Color= GameManger::Instance->players[0]->Get_Color();
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

<<<<<<< HEAD
//void Create_Item(std::vector<Item>& items, int gridSize)
//{
//	// 아이템 타입 (0 ~ 2 랜덤)
//	// int randomType = rand() % 3;
//	int randomType = 1;
//
//	// 아이템 위치 (랜덤 좌표 생성)
//	float x = static_cast<float>((rand() % gridSize) - gridSize / 2);
//	float y = 0.0f; // 고정 Y 좌표
//	float z = static_cast<float>((rand() % gridSize) - gridSize / 2);
//	glm::vec3 randomLocation = glm::vec3(x, y, z);
//
//	// 새로운 아이템 생성
//	Item newItem(randomType, randomLocation);
//
//	// 리스트에 추가
//	items.push_back(newItem);
//
//	// 확인용
//	std::cout << "Item created: Type=" << randomType << ", Location=("
//		<< x << ", " << y << ", " << z << ")" << std::endl;
//}

=======
>>>>>>> 理쒖젙誘�
void Send_Object()
{
	char pbuffer[sizeof(Player)];
	GameManger::Instance->players[0]->serializePlayer(pbuffer);
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

	if ((currentTime - timer.getLastItemTime()) >= 5)			// 아이템 생성 이벤트
	{
		// 아이템 생성
		std::cout << currentTime - timer.getLastItemTime() << std::endl;
		EventQueue::currentInstance->addEvent(std::bind(&Item::Create_Item, items));
		timer.setLastItemTime(currentTime);       // 마지막 생성 시간 갱신
	}

	EventQueue::currentInstance->addEvent(std::bind(&Timer::Update_Timer,
		currentTime- timer.getStartTime()));

	if (timer.isFinished())
	{
		// 게임 끝내는 이벤트 생성
	}
}