#include "State.h"
#include "CTimer.h"

Play_State::Play_State()
{
	glm::mat4 Tscale = glm::mat4(1.0f);
	Tscale = glm::scale(Tscale, glm::vec3(0.5f, 0.5f, 1.0f));

	Time_Count[0].Tlocate = glm::vec3(0.25f, 0.5f, 0.0f);
	Time_Count[1].Tlocate = glm::vec3(0.60f, 0.5f, 0.0f);

	for (int i = 0; i < 2; ++i) {
		glm::mat4 Tx = glm::mat4(1.0f);
		Time_Count[i].Ttr = glm::mat4(1.0f);

		Tx = glm::translate(Tx, Time_Count[i].Tlocate);
		Time_Count[i].Ttr = Tx * Tscale * Time_Count[i].Ttr; // Tscale 추가
	}

	glm::mat4 Sscale = glm::mat4(1.0f);
	Sscale = glm::scale(Sscale, glm::vec3(0.2f, 0.5f, 1.0f));

	Score[0].Tlocate = glm::vec3(0.10f, 0.5f, 0.0f);
	Score[1].Tlocate = glm::vec3(0.45f, 0.5f, 0.0f);
	Score[2].Tlocate = glm::vec3(0.80f, 0.5f, 0.0f);

	for (int i = 0; i < 3; ++i) {
		glm::mat4 Tx = glm::mat4(1.0f);
		Score[i].Ttr = glm::mat4(1.0f);

		Tx = glm::translate(Tx, Score[i].Tlocate);
		Score[i].Ttr = Tx * Tscale * Score[i].Ttr; // Tscale 추가
	}

	Num[0] = CreateTexture("0.png");
	Num[1] = CreateTexture("1.png");
	Num[2] = CreateTexture("2.png");
	Num[3] = CreateTexture("3.png");
	Num[4] = CreateTexture("4.png");
	Num[5] = CreateTexture("5.png");
	Num[6] = CreateTexture("6.png");
	Num[7] = CreateTexture("7.png");
	Num[8] = CreateTexture("8.png");
	Num[9] = CreateTexture("9.png");
	Num[10] = CreateTexture("comg_bg.png");
}

// recv Thread 이거 맞는지 확인 가능할까요?
void Play_State::enter() {
	/*while (true) {
		if (key_change) {
			send(playerInput, sizeof(playerInput));
			key_change = false;
		}
		Parent_pakcet packet;
		// 패킷개수를고정크기로recv
			for (int i = 0; i < 패킷 개수; i++)
			{
				recv(client_socket, &packet, sizeof(packet), 0)
					handlePacket(packet)
			}
		// 카메라업데이트
			// 오브젝트렌더
	}
	void handlePacket(const Parent_packet & packet) {
		switch (packet.packet_type) {
		case move_player:
			const Move_Player& move_packet = static_cast<const
				Move_Player&>(packet);
			// 해당하는처리
		case create_bullet:
			const Create_bullet& Create_bpacket = static_cast<const
				Create_bullet&>(packet);
			// 해당하는처리
				.
				.
		}
	}*/
	//player.Set_Action((KeyInput)0);
}


void Play_State::Update()
{
	//time_t u = time(NULL); 
	


	//player.Calculate_Move();
	//if (key_change) {
	//	send(playerInput, sizeof(playerInput));
	//	key_change = false;
	//}
	
	char keyinput = player.Get_Action();
	send(sock, &keyinput, sizeof(char), 0);
	
	//Parent_pakcet packet;

	//패킷개수를고정크기로recv
	char size_buffer[sizeof(int)];
	recv(sock, size_buffer, sizeof(int), 0);
	int queue_size = *reinterpret_cast<int*>(size_buffer);
		for (int i = 0; i < queue_size; i++)
		{
			char buffer[128];
			size_t len = recv(sock, buffer, sizeof(buffer), 0);
			process_received_data(buffer, len,&player,All_Box,bullet,item,Time);
			//handlePacket(packet)
		}
	
	//char buffer[sizeof(Player)];
	//recv(sock, buffer, sizeof(buffer), 0);
	//player.deserializePlayer(buffer);

	//카메라업데이트
	player.Calculate_Camera();

	//	오브젝트렌더
}

void Play_State::Draw()
{
	// 깊이 테스트 활성화 및 뷰포트 설정
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1260, 700);

	// 셰이더 유니폼 위치 가져오기
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");

	// 투영 행렬 및 뷰 행렬 설정
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f);
	projection = glm::rotate(projection, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::translate(projection, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 view = glm::lookAt(player.Get_Camerapos(), player.Get_Camerapos() + player.Get_Cameradirection(), cameraUp);

	// 유니폼 값 전송
	glUseProgram(s_program);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	// 유니폼 위치 가져오기
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	unsigned int modelLocation1 = glGetUniformLocation(s_program, "in_Color");

	// VAO 바인딩
	glBindVertexArray(vao);

	// 박스 렌더링
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glUniform3f(modelLocation1, All_Box[i][j].Get_R(), All_Box[i][j].Get_G(), All_Box[i][j].Get_B());
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(All_Box[i][j].TR));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
		}
	}

	// 총알 렌더링
	if (bullet[0].View) {
		glm::mat4 TR1 = glm::translate(glm::mat4(1.0f), bullet[0].Blocate) * bullet[0].TR;
		glUniform3f(modelLocation1, bullet[0].Bcolor[0], bullet[0].Bcolor[1], bullet[0].Bcolor[2]);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
	}

	// 아이템 렌더링
	for (int i = 0; i < 12; i++) {
		if (item[i].View) {
			glm::mat4 TR1 = glm::translate(glm::mat4(1.0f), item[i].ILocate) * item[i].TR;
			glUniform3f(modelLocation1, item[i].Icolor[0], item[i].Icolor[1], item[i].Icolor[2]);
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
		}
	}

	// 플레이어 렌더링
	glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), player.Get_Plocate() + player.Get_Move()) * player.Get_TR();
	glUniform3f(modelLocation1, player.Get_R(), player.Get_G(), player.Get_B());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(playerModel));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
	
	{
		// 깊이 테스트 비활성화
		glDisable(GL_DEPTH_TEST);
		glViewport(540, 500, 200, 200);

		// 셰이더 프로그램 활성화
		glBindVertexArray(triangleVertexArrayObject);
		glUseProgram(triangleShaderProgramID);

		// 직교 투영 행렬 및 유니폼 설정
		projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
		view = glm::mat4(1.0f);

		glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "projectionTransform"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "viewTransform"), 1, GL_FALSE, glm::value_ptr(view));

		// 첫 번째 숫자 위치 및 크기 설정
		glm::mat4 Tscale = glm::mat4(1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Num[Time/10]);
		// 첫 번째 숫자
		glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "modelTransform"), 1, GL_FALSE, glm::value_ptr(Time_Count[0].Ttr));
		glDrawArrays(GL_TRIANGLES, 0, 6); // 숫자 텍스처 렌더링

		glBindTexture(GL_TEXTURE_2D, Num[Time % 10]);
		// 두 번째 숫자
		glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "modelTransform"), 1, GL_FALSE, glm::value_ptr(Time_Count[1].Ttr));
		glDrawArrays(GL_TRIANGLES, 0, 6); // 숫자 텍스처 렌더링
	}

	{
		glDisable(GL_DEPTH_TEST);
		glViewport(100, 550, 150, 150);
		Draw_Score(player);

		glViewport(1000, 550, 150, 150);
		Draw_Score(player);
	}

	//glDisable(GL_DEPTH_TEST);
	//glViewport(830, 500, 200, 200);
	//Draw_filed(false);

	//glViewport(530, 500, 200, 200);
	//Draw_time();

	//glViewport(100, 550, 150, 150);
	////Draw_num(player[0].Occupy_box);

	//glViewport(1000, 550, 150, 150);
	////Draw_num(player[1].Occupy_box);

	//if (Game_over) {
	//	glViewport(530, 300, 200, 200);
	//	Whos_win();
	//}
}

void Play_State::SKeyDown(int key) {
	switch (key) {
	case GLUT_KEY_UP:
		player.Set_DownAction(KEY_UP);
		break;
	case GLUT_KEY_DOWN:
		player.Set_DownAction(KEY_DOWN);
		break;
	case GLUT_KEY_LEFT:
		player.Set_DownAction(KEY_LEFT);
		break;
	case GLUT_KEY_RIGHT:
		player.Set_DownAction(KEY_RIGHT);
		break;

	}
}


void Play_State::SKeyUp(int key) {
	switch (key) {
	case GLUT_KEY_UP:
		player.Set_UpAction(KEY_UP);
		break;
	case GLUT_KEY_DOWN:
		player.Set_UpAction(KEY_DOWN);
		break;
	case GLUT_KEY_LEFT:
		player.Set_UpAction(KEY_LEFT);
		break;
	case GLUT_KEY_RIGHT:
		player.Set_UpAction(KEY_RIGHT);
		break;
	}
}

void Play_State::KeyUp(int key)
{
	switch (key) {
	case 'a':
		player.Set_UpAction(KEY_A);
	}
}

void Play_State::KeyDown(int key)
{
	switch (key) {
	case 'a':
		player.Set_DownAction(KEY_A);
	}
}

void Play_State::Draw_Score(Player& player)
{
	// 셰이더 프로그램 활성화
	glBindVertexArray(triangleVertexArrayObject);
	glUseProgram(triangleShaderProgramID);

	// 직교 투영 행렬 및 유니폼 설정
	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "projectionTransform"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "viewTransform"), 1, GL_FALSE, glm::value_ptr(view));

	// 첫 번째 숫자 위치 및 크기 설정
	glm::mat4 Tscale = glm::mat4(1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Num[player.Get_Box()/100]);
	// 첫 번째 숫자
	glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "modelTransform"), 1, GL_FALSE, glm::value_ptr(Score[0].Ttr));
	glDrawArrays(GL_TRIANGLES, 0, 6); // 숫자 텍스처 렌더링

	glBindTexture(GL_TEXTURE_2D, Num[player.Get_Box() % 100/10]);
	// 두 번째 숫자
	glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "modelTransform"), 1, GL_FALSE, glm::value_ptr(Score[1].Ttr));
	glDrawArrays(GL_TRIANGLES, 0, 6); // 숫자 텍스처 렌더링

	glBindTexture(GL_TEXTURE_2D, Num[player.Get_Box() % 10]);
	glUniformMatrix4fv(glGetUniformLocation(triangleShaderProgramID, "modelTransform"), 1, GL_FALSE, glm::value_ptr(Score[2].Ttr));
	glDrawArrays(GL_TRIANGLES, 0, 6); // 숫자 텍스처 렌더링
}

Stay_State::Stay_State()
{
	glm::mat4 Tscale = glm::mat4(1.0f);
	Tscale = glm::scale(Tscale, glm::vec3(2.0f, 2.0f, 2.0f));
	
	Logo_texture.Ttr = Tscale * glm::mat4(1.0f);
	Logo_texture.text = CreateTexture("Logo_state.png");
}

void Stay_State::Draw()
{
	glEnable(GL_DEPTH_TEST);
	unsigned int Texture_viewlocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	unsigned int Texture_projectionlocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform");

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0)); // 공간을 뒤로 미룸

	// 셰이더 프로그램 사용
	glUseProgram(triangleShaderProgramID);

	// 텍스처 유닛 설정
	glUniform1i(glGetUniformLocation(triangleShaderProgramID, "tex"), 0);
	glUniformMatrix4fv(Texture_projectionlocation, 1, GL_FALSE, &projection[0][0]);

	// 뷰 행렬 설정
	glm::mat4 view = glm::mat4(1.0f);
	unsigned int viewLocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	// 모델 변환 행렬 설정
	unsigned int modelLocation = glGetUniformLocation(triangleShaderProgramID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Logo_texture.Ttr)); // 모델 변환 적용

	// 텍스처 바인딩
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Logo_texture.text);

	// 버텍스 배열 바인딩
	glBindVertexArray(triangleVertexArrayObject);

	// 그리기 호출
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 뷰포트 설정
	glViewport(0, 0, 1260, 700);
}

void Stay_State::KeyDown(int key)
{
	if (key == 'a')
		FrameWork::currentInstance->Exit_State();
}