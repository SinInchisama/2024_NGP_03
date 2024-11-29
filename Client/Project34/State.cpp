#include "State.h"
#include "CTimer.h"

Play_State::Play_State()
{

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
	//	for (int i = 0; i < 패킷 개수; i++)
	//	{
	//		recv(client_socket, &packet, sizeof(packet), 0)
	//			handlePacket(packet)
	//	}
	
	char buffer[sizeof(Player)];
	recv(sock, buffer, sizeof(buffer), 0);
	player.deserializePlayer(buffer);

	//카메라업데이트
	player.Calculate_Camera();

	//	오브젝트렌더
}

void Play_State::Draw()
{
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정


	glm::mat4 Prev_rotation = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f);
	projection = glm::rotate(projection, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3)); //--- 공간을 약간 뒤로 미뤄줌
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));


	view = glm::lookAt(player.Get_Camerapos(), player.Get_Camerapos() + player.Get_Cameradirection(), cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glUseProgram(triangleShaderProgramID);

	unsigned int Texture_viewlocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	unsigned int Teture_projectionlocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform");

	glUniformMatrix4fv(Texture_viewlocation, 1, GL_FALSE, &view[0][0]);

	glUniformMatrix4fv(Teture_projectionlocation, 1, GL_FALSE, &projection[0][0]);

	glViewport(0, 0, 1260, 700);
	glUseProgram(s_program);

	GLint success;
	glGetProgramiv(s_program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(s_program, 512, NULL, infoLog);
		std::cerr << "Error linking triangle shader program: " << infoLog << std::endl;
	}

	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	unsigned int modelLocation1 = glGetUniformLocation(s_program, "in_Color"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기


	glBindVertexArray(vao);


	for (int i = 0; i < 20; i = i++) {					// 박스를 그려주는 부분.
		for (int j = 0; j < 20; j++) {

			glUniform3f(modelLocation1, All_Box[i][j].Get_R(), All_Box[i][j].Get_G(), All_Box[i][j].Get_B());

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(All_Box[i][j].TR)); //--- modelTransform 변수에 변환 값 적용하기
			
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
		}
	}

	//for (int i = 0; i < 12; i++) {
	//	if (item[i].View) {
	//		glUniform3f(modelLocation1, item[i].Icolor[0], item[i].Icolor[1], item[i].Icolor[2]);

	//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(item[i].TR)); //--- modelTransform 변수에 변환 값 적용하기
	//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
	//	}
	//}

	glm::mat4 TR1 = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);

	Tx = glm::mat4(1.0f);


	glUniform3f(modelLocation1, player.Get_R(), player.Get_G(), player.Get_B());

	Tx = glm::translate(Tx, player.Get_Plocate() + player.Get_Move());
	TR1 = Tx * player.Get_TR();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변환 값 적용하기
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
	

	//if (View_draw_background) {
	//	glUseProgram(triangleShaderProgramID);
	//	glBindVertexArray(triangleVertexArrayObject);

	//	glUniform1i(glGetUniformLocation(triangleShaderProgramID, "tex"), 0);

	//	unsigned int modelLocation2 = glGetUniformLocation(triangleShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	//	for (int i = 0; i < 4; i++) {
	//		glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(Worldbox[i].Ttr)); //--- modelTransform 변수에 변환 값 적용하기

	//		glActiveTexture(GL_TEXTURE0);						// 뒷자리 숫자
	//		glBindTexture(GL_TEXTURE_2D, texureId[10]);
	//		glDrawArrays(GL_TRIANGLES, 0, 6);
	//	}
	//}
	glUseProgram(s_program);


	//view = glm::lookAt(player[1].Get_Camerapos(), player[1].Get_Camerapos() + player[1].Get_Cameradirection(), cameraUp);
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//glUseProgram(triangleShaderProgramID);
	//glUniformMatrix4fv(Texture_viewlocation, 1, GL_FALSE, &view[0][0]);


	//glViewport(630, 0, 630, 700);
	//Draw_filed(true);

	//view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	//glm::mat4 projection = glm::mat4(1.0f);
	//projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 100.0f);
	//projection = glm::rotate(projection, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0)); //--- z축에 대하여 회전 행렬
	//projection = glm::translate(projection, glm::vec3(0.0, -3.0, 15.0)); //--- 공간을 약간 뒤로 미뤄줌
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//glUseProgram(triangleShaderProgramID);

	//glUniformMatrix4fv(Texture_viewlocation, 1, GL_FALSE, &view[0][0]);

	//glUniformMatrix4fv(Teture_projectionlocation, 1, GL_FALSE, &projection[0][0]);

	//glDisable(GL_DEPTH_TEST);
	//glViewport(830, 500, 200, 200);
	//Draw_filed(false);


	//glViewport(180, 500, 200, 200);
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

	}
}

void Play_State::KeyDown(int key)
{
	switch (key) {

	}
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