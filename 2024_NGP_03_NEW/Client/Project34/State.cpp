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
	// 데이터 수신
	char cbuffer;
	recv(sock, &cbuffer, sizeof(cbuffer), 0);
	My_index = cbuffer;

	char buffer[sizeof(Player)];
	int result = recv(sock, buffer, sizeof(buffer), 0);
	if (result > 0) {
			player[0].deserializePlayer(buffer);
			player[1].deserializePlayer(buffer);
	}
	result = recv(sock, buffer, sizeof(buffer), 0);
	player[1].deserializePlayer(buffer);
	char bbuffer[sizeof(Box)];
	for (int i = 0; i < 20; ++i) {
		for (int k = 0; k < 20; ++k) {
			recv(sock, bbuffer, sizeof(bbuffer), 0);
			All_Box[i][k].deserializeBox(bbuffer);
		}
	}
}


void Play_State::Update()
{

	char keyinput = player[My_index].Get_Action();
	send(sock, &keyinput, sizeof(char), 0);

	char int_b[sizeof(int)];
	int buffer_size;

	int retval;
	retval = recv(sock, (char*)&buffer_size, sizeof(buffer_size), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		std::cerr << "Play_State:::Update() buffer_size recv SOCKET_ERROR occured\n";
		return;
	}
	
	char recv_buffer[1024];
	if (buffer_size == 0) {
		std::cerr << "Play_State::Update() buffer_size is 0\n";
		return;
	}
	retval = recv(sock, recv_buffer, buffer_size, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		std::cerr << "Play_State::Update() recv_buffer recv SOCKET_ERROR occured.\n";
		return;
	}
	else if (retval < 1) {
		std::cerr << "PlayState::Update() recv_buffer is too small!\n";
		return;
	}

	int current_pos{};
	char* p = recv_buffer;
	int offset{};
	while (current_pos < buffer_size)/*조건문 수정 필요할 수도 있음*/ {
		char packet_type = p[0];
		if (packet_type == PACKET_MOVE_PLAYER) {
			Move_Packet packet;
			offset = packet.deserializePlayer(p);
			player[packet.player_index].Set_Move(packet.move); 
		}
		else if (packet_type == PACKET_CREATE_BULLET) {
			Create_bullet packet;
			offset = packet.deserializePlayer(p);
			bullet[packet.player_index].View = packet.b;
		}
		else if (packet_type == PACKET_CREATE_ITEM) {
			Create_item packet;
			offset = packet.deserializePlayer(p);
			item[packet.item_index].Icolor = packet.color;
			item[packet.item_index].ILocate = packet.locate;
			item[packet.item_index].View = true;
		}
		else if (packet_type == PACKET_DELETE_ITEM) {
			Delete_item packet;
			offset = packet.deserializePlayer(p);
			item[packet.item_index].View = false;
		}
		else if (packet_type == PACKET_DELETE_BULLET) {
			Delete_bullet packet;
			offset = packet.deserializePlayer(p);
			bullet[packet.bullet_index].View = false;
			// std::cout << "INDEX " << (int)packet.bullet_index << "'s Bullet has deleted.\n";
		}
		else if (packet_type == PACKET_CHANGE_FLOOR) {
			Change_floor packet;
			offset = packet.deserializePlayer(p);
			All_Box[packet.box_index / 20][packet.box_index % 20].Color = packet.color;
			// std::cerr << "Unknown packet type: " << static_cast<int>(packet_type) << "\n";
		}
		else if (packet_type == PACKET_MOVE_BULLET) {
			Move_bullet packet;
			offset = packet.deserializePlayer(p);
			bullet[packet.player_index].Blocate = packet.position;
			std::cout << packet.position.x << "   " << packet.position.y << "   " << packet.position.z << "   " << std::endl;
		}
		else if (packet_type == PACKET_UPDATE_TIMER) {
			Update_timer packet;
			offset = packet.deserializePlayer(p);
			Time = packet.timer;
		}
		else if (packet_type == PACKET_UPDATE_SCORE) {
			Update_Score packet;
			offset = packet.deserializePlayer(p);
			player[0].Set_Box(packet.My_score);
			player[1].Set_Box(packet.Enermy_score);
		}
		else {
			std::cout << "Exit State\n";
			FrameWork::currentInstance->Exit_State();
			End_game packet;
			packet.deserializePlayer(p);
			Win = packet.player_index;
			return;
		}
		p += offset;
		current_pos += offset;
	}

	//카메라업데이트
	player[My_index].Calculate_Camera();

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
	unsigned int Texture_viewlocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	unsigned int Teture_projectionlocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform");

	glm::mat4 view = glm::lookAt(Camerapos, Camerapos + Cameradirection, Cameraup);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 100.0f);
	projection = glm::rotate(projection, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0)); //--- z축에 대하여 회전 행렬
	projection = glm::translate(projection, glm::vec3(0.0, -3.0, 15.0)); //--- 공간을 약간 뒤로 미뤄줌
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	// 유니폼 값 전송
	glUseProgram(s_program);

	glUniformMatrix4fv(Texture_viewlocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(Teture_projectionlocation, 1, GL_FALSE, &projection[0][0]);
	/*glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));*/

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
	for (int i = 0; i < 2; ++i) {
		glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), player[i].Get_Plocate() + player[i].Get_Move()) * player[i].Get_TR();
		glUniform3f(modelLocation1, player[i].Get_R(), player[i].Get_G(), player[i].Get_B());
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(playerModel));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));

		// 총알 렌더링
		if (bullet[i].View) {
			glm::mat4 TR1 = glm::translate(glm::mat4(1.0f), bullet[i].Blocate) * bullet[i].TR;
			glUniform3f(modelLocation1, bullet[i].Bcolor[0], bullet[i].Bcolor[1], bullet[i].Bcolor[2]);
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
		}
	}
	
	{
		// 깊이 테스트 비활성화
		glDisable(GL_DEPTH_TEST);
		glViewport(540, 580, 200, 200);

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
		glViewport(100, 600, 150, 150);
		Draw_Score(player[0]);

		glViewport(1000, 600, 150, 150);
		Draw_Score(player[1]);
	}

}

void Play_State::SKeyDown(int key) {
	switch (key) {
	case GLUT_KEY_UP:
		player[My_index].Set_DownAction(KEY_UP);
		break;
	case GLUT_KEY_DOWN:
		player[My_index].Set_DownAction(KEY_DOWN);
		break;
	case GLUT_KEY_LEFT:
		player[My_index].Set_DownAction(KEY_LEFT);
		break;
	case GLUT_KEY_RIGHT:
		player[My_index].Set_DownAction(KEY_RIGHT);
		break;

	}
}


void Play_State::SKeyUp(int key) {
	switch (key) {
	case GLUT_KEY_UP:
		player[My_index].Set_UpAction(KEY_UP);
		break;
	case GLUT_KEY_DOWN:
		player[My_index].Set_UpAction(KEY_DOWN);
		break;
	case GLUT_KEY_LEFT:
		player[My_index].Set_UpAction(KEY_LEFT);
		break;
	case GLUT_KEY_RIGHT:
		player[My_index].Set_UpAction(KEY_RIGHT);
		break;
	}
}

void Play_State::KeyUp(int key)
{
	switch (key) {
	case 'a':
		player[My_index].Set_UpAction(KEY_A);
	}
}

void Play_State::KeyDown(int key)
{
	switch (key) {
	case 'a':
		player[My_index].Set_DownAction(KEY_A);
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

void Stay_State::Update()
{
	char size_buffer[sizeof(int)];
	recv(sock, size_buffer, sizeof(int), 0);
	FrameWork::currentInstance->Exit_State();
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

End_State::End_State()
{
	glm::mat4 Tscale = glm::mat4(1.0f);
	Tscale = glm::scale(Tscale, glm::vec3(2.0f, 2.0f, 2.0f));

	Win_texture[0].Ttr = Tscale * glm::mat4(1.0f);
	Win_texture[1].Ttr = Tscale * glm::mat4(1.0f);

	Win_texture[0].text = CreateTexture("1p_win.png");
	Win_texture[1].text = CreateTexture("2p_win.png");
}

void End_State::Draw()
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
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Win_texture[Win].Ttr)); // 모델 변환 적용

	// 텍스처 바인딩
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Win_texture[Win].text);

	// 버텍스 배열 바인딩
	glBindVertexArray(triangleVertexArrayObject);

	// 그리기 호출
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 뷰포트 설정
	glViewport(0, 0, 1260, 700);
}
