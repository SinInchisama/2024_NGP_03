#include "WorkThread.h"

Player players[2] = { {0, {0.0f, 0.0f, 0.0f}},{0, {0.0f, 0.0f, 0.0f}} };
Box All_Box[20][20];
Timer timer(60);

// Å¬¶óÀÌ¾ğÆ®¿Í µ¥ÀÌÅÍ Åë½Å
DWORD WINAPI WorkThread(LPVOID arg)
{
	Reset_Object();
	
	// send(¿ÀºêÁ§Æ®);
	Send_Object();

	//previousTime = std::chrono::high_resolution_clock::now();
	timer.resetTimer();

	while (true) {
		recv(client_sock[1], &cbuffer, sizeof(cbuffer), 0);
		Timer_Check();

		// ÀÓ°è ¿µ¿ª ÁøÀÔ

		// EventQueue::currentInstance->executeAll();

		// ÀÓ°è ¿µ¿ª Å»Ãâ

		// Çà·Ä º¯È¯(ÇÃ·¹ÀÌ¾î, ÃÑ¾Ë ¿òÁ÷ÀÓ)
		if (cbuffer == 0) {
			std::cout << (int)cbuffer << std::endl;
		}
		players[0].Set_Action(cbuffer);
		players[0].Calculate_Move();
		//char pbuffer[sizeof(Player)];
		//players[0].serializePlayer(pbuffer);
		//int result = send(client_sock[1], pbuffer, sizeof(pbuffer), 0);

		// Ãæµ¹ Ã¼Å©

		// Àü¼ÛÇÒ ÆĞÅ¶¸®½ºÆ® °³¼ö Àü¼Û(°íÁ¤Å©±â)

<<<<<<< HEAD
		// for¹®À¸·Î ÆĞÅ¶ º¸³»±â
=======
		// Å¬¶óÀÌ¾ğÆ®·Î Å¥ÀÇ Å©±â Àü¼Û
		packetQueue.push(std::make_unique<Move_Packet>(1, players[0].Get_Move()));

		char size_buffer[sizeof(int)];
		int queue_size = packetQueue.size();
		std::memcpy(size_buffer, &queue_size, sizeof(int));
		send(client_sock[1], size_buffer, sizeof(size_buffer), 0);

		// packetQueue°¡ ºô ¶§±îÁö ¼ÒÄÏµ¥ÀÌÅÍ¸¦ º¸³¿.
		while (!packetQueue.empty()) {
			char buffer[128];
			std::unique_ptr<Parent_Packet> packet = std::move(packetQueue.front());
			packetQueue.pop();
			// ÆĞÅ¶ Á÷·ÄÈ­
			packet->serialize(buffer);
			send(client_sock[1], buffer, sizeof(buffer), 0);
		}
>>>>>>> ê¹€ì„ ë¹ˆ
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

			Scale = glm::scale(Scale, glm::vec3(xScale,yScale,zScale)); //		°¢ »ç°¢Çü Å©±â 
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
	timer.setDeltaTime(static_cast<float>(currentTime - timer.getPreviousTime())); // ÇÁ·¹ÀÓ °è»ê
	timer.setPreviousTime(currentTime);

	if ((currentTime - timer.getStartTime()) % 5)			// ¾ÆÀÌÅÛ »ı¼º ÀÌº¥Æ®
	{
		// ¾ÆÀÌÅÛ »ı¼º
	}

	if (timer.isFinished())
	{
		// °ÔÀÓ ³¡³»´Â ÀÌº¥Æ® »ı¼º
	}
}