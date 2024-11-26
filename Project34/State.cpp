#include "State.h"

void Play_State::Draw()
{
	//unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	//unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정


	//glm::mat4 Prev_rotation = glm::mat4(1.0f);

	//view = glm::mat4(1.0f);
	//projection = glm::mat4(1.0f);
	//projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f);
	//projection = glm::rotate(projection, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3)); //--- 공간을 약간 뒤로 미뤄줌
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));


	//view = glm::lookAt(player[0].Get_Camerapos(), player[0].Get_Camerapos() + player[0].Get_Cameradirection(), cameraUp);
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//glUseProgram(triangleShaderProgramID);

	//unsigned int Texture_viewlocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	//unsigned int Teture_projectionlocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform");

	//glUniformMatrix4fv(Texture_viewlocation, 1, GL_FALSE, &view[0][0]);

	//glUniformMatrix4fv(Teture_projectionlocation, 1, GL_FALSE, &projection[0][0]);

	//glViewport(0, 0, 630, 700);
	//Draw_filed(true);


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
