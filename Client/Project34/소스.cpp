#pragma comment(lib, "lib/freeglut.lib")
#pragma comment(lib, "lib/Freeimage.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

#include <random>

#include <iostream>
#include "include/GL/glew.h" // 필요한 헤더파일 include
#include "include/GL/freeglut.h"
#include "include/GL/freeglut_ext.h"
#include "include/GL/glut.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include <random>
#include <time.h>

#include "CPlayer.h"
#include "CBox.h"
#include "CItem.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "FrameWork.h"

using namespace std;

void TimerFunction(int value);
void SKeyDownboard(int key, int x, int y);
void SKeyUpboard(int key, int x, int y);
GLvoid KeyDownboard(unsigned char key, int x, int y);
GLvoid KeyUpboard(unsigned char key, int x, int y);
void Logo_state();
void Create_item();

void init();

void Crash(int num, int inspection);
int collide(Player* p, Box b, glm::mat4 TR);
int item_collide(Player* p, Item i, glm::mat4 TR);

void Item_zero(Player* p, Item i);
void Item_one(Player* p, Item i);

void Draw_time();
void Draw_num(int num);
void Whos_win();

float Cameraz = 15.0f;
float Camerax = 0.0f;
float ySelfRot = 0.0f;
float yZeroRot = 0.0f;
float Viewz = -1.0f;
float Viewy = 15.0f;
float BlockSpeed = 0.0f;

bool ra, Drop = true, Game_over, Game_start;
int xcount = 20, zcount = 20;
int Itemcount = 0;
time_t Now_time, start_time, Creat_time;

float yz = 0.0f;
//Texture Timecount[2];
//Texture Score[3];

//Texture Worldbox[4];

Item item[20];

GLUquadricObj* qobj = gluNewQuadric();

glm::vec3 cameraPos;
glm::vec3 cameraPos_1;
glm::vec3 cameraDirection; //--- 카메라 바라보는 방향
glm::vec3 cameraDirection_1;

glm::vec3 originPos;

GLuint texureId[11];
GLuint Who_win[2];

FrameWork* FrameWork::currentInstance = nullptr;


int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1260, 700);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	FrameWork framework;  // 전역 변수로 FrameWork 객체 생성
	FrameWork::currentInstance = &framework;

	//Texture_init();

	init();
	glewInit();
	framework.Init_Shader();
	framework.init_Buffer();
	glutDisplayFunc(FrameWork::DisplayWrapper);
	glutReshapeFunc(FrameWork::DisplayReShape);
	glutKeyboardFunc(KeyDownboard); // 키보드 입력 콜백함수 지정
	glutKeyboardUpFunc(KeyUpboard);
	glutSpecialFunc(SKeyDownboard);
	glutSpecialUpFunc(SKeyUpboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();
}

void TimerFunction(int value) {
	FrameWork::currentInstance->Update(value);
	//framework.Update();
	//time_t u = time(NULL);

	//if (!Game_over && Game_start) {
	//	for (int i = 0; i < 2; i++) {
	//		player[i].Calculate_Move();

	//		int temp = 0;

	//		glm::mat4 TR = glm::mat4(1.0f);
	//		glm::mat4 Tx = glm::mat4(1.0f);
	//		glm::mat4 Scale = glm::mat4(1.0f);

	//		TR = glm::mat4(1.0f);					// 플레이어를 그려주는 부분.
	//		Tx = glm::mat4(1.0f);
	//		Scale = glm::mat4(1.0f);


	//		Scale = glm::scale(Scale, player[i].Get_Pscale()); //		플레이어
	//		Tx = glm::translate(Tx, player[i].Get_Plocate() + player[i].Get_Move());
	//		TR = Tx * Scale;

	//		for (int a = 0; a < xcount; a++) {
	//			for (int k = 0; k < zcount; k++) {
	//				temp = collide(&player[i], All_Box[a][k], TR);
	//				if (temp != -1) {
	//					Crash(i, temp);
	//				}
	//			}
	//		}

	//		temp = 0;

	//		for (int a = 0; a < 12; a++) {
	//			if (item[a].View == true) {
	//				temp = item_collide(&player[i], item[a], TR);
	//				if (temp != -1) {
	//					if (item[a].Item_type == 0)
	//						Item_zero(&player[i], item[a]);
	//					else if (item[a].Item_type == 1)
	//						Item_one(&player[i], item[a]);
	//					
	//					item[a].View = false;
	//					break;
	//				}
	//			}
	//		}
	//		// 움직이고나서 해당 위치 블록 체크	(현재는 배열로 체크하는 중. 배열로 체크시 각 꼭짓점마다 이전 위치 저장해줘야할듯?)
	//		//Player_camera(&player[i]);																// 플레이어 카메라 위치 계산.
	//		player[i].Calculate_Camera();

	//		// 해결해야되는 코드
	//		/*player[i].Move[1] -= player[i].gravity;
	//		if (player[i].Move[1] < -3.0) {
	//			player[i].Plocate = All_Box[19 * i][19 * i].Blocate;
	//			player[i].Plocate[1] = 0.0f;
	//			player[i].Move = { 0.0f,0.0f,0.0f };
	//		}
	//		if (Now_time - player[i].timer >= 1) {
	//			player[i].stop = false;
	//		}*/

	//	}
	//	
	//	Now_time = u - start_time;
	//	if ((u - Creat_time )%5 == 0) {
	//		item[Itemcount++].View = true;
	//		Creat_time = u + 4;
	//	}

	//	if (Now_time == 60) 
	//		Game_over = true;

	//}

	glutTimerFunc(50, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid KeyDownboard(unsigned char key, int x, int y) {
	FrameWork::currentInstance->KeyDownboard(key,x,y);
	//else {
	//	//if (!player[1].stop && player[1].Move[1] == 0) {
	//		if (key == 'a') {
	//			player[1].Set_X(-1);
	//		}
	//		else if (key == 'd') {
	//			player[1].Set_X(+1);
	//		}
	//		else if (key == 'w') {
	//			player[1].Set_Z(-1);
	//		}
	//		else if (key == 's') {
	//			player[1].Set_Z(1);
	//		}
	//	//	else if (key == 'q')
	//	//		player[1].lotate += 10;
	//	//	else if (key == 'e')
	//	//		player[1].lotate -= 10;
	//	//}
	//	//if (!player[0].stop && player[0].Move[1] == 0) {
	//	//	if (key == ',')
	//	//		player[0].lotate += 10;
	//	//	else if (key == '.')
	//	//		player[0].lotate -= 10;
	//	//}
	//	if (key == 'r' && Game_over)
	//		init();
	//		
	//}
	glutPostRedisplay();
}

GLvoid KeyUpboard(unsigned char key, int x, int y) {
	FrameWork::currentInstance->KeyUpboard(key, x, y);
}

void SKeyDownboard(int key, int x, int y) {
	FrameWork::currentInstance->SKeyDownboard(key,x,y);
}

void SKeyUpboard(int key, int x, int y) {
	FrameWork::currentInstance->SKeyUpboard(key, x, y);
}


//void Texture_init() {
//	Timecount[0].Tlocate = glm::vec3(0.5f, 0.0f, 0.0f);
//	Timecount[1].Tlocate = glm::vec3(-0.5f, 0.0f, 0.0f);
//
//	for (int i = 0; i < 2; i++) {
//		glm::mat4 Tx = glm::mat4(1.0f);
//		Timecount[i].Ttr = glm::mat4(1.0f);
//
//		Tx = glm::translate(Tx, Timecount[i].Tlocate);
//		Timecount[i].Ttr = Tx * Timecount[i].Ttr;
//	}
//
//	for (int i = 0; i < 3; i++) {
//		Score[i].Tlocate = glm::vec3(-0.66f + 0.66 * i, 0.0f, 0.0f);
//		glm::mat4 Tx = glm::mat4(1.0f);
//		Score[i].Ttr = glm::mat4(1.0f);
//
//		Tx = glm::translate(Tx, Score[i].Tlocate);
//		Score[i].Ttr = Tx * Score[i].Ttr;
//	}
//
//
//	glm::mat4 Tscale = glm::mat4(1.0f);
//	Tscale = glm::scale(Tscale, glm::vec3(2.0f, 2.0f, 2.0f));
//	Logo_texture.Ttr = Tscale * glm::mat4(1.0f);
//
//	Logo = CreateTexture("Logo_state.png");
//	texureId[0] = CreateTexture("0.png");
//	texureId[1] = CreateTexture("1.png");
//	texureId[2] = CreateTexture("2.png");
//	texureId[3] = CreateTexture("3.png");
//	texureId[4] = CreateTexture("4.png");
//	texureId[5] = CreateTexture("5.png");
//	texureId[6] = CreateTexture("6.png");
//	texureId[7] = CreateTexture("7.png");
//	texureId[8] = CreateTexture("8.png");
//	texureId[9] = CreateTexture("9.png");
//	texureId[10] = CreateTexture("comg_bg.png");
//
//	Who_win[0] = CreateTexture("1_win.png");
//	Who_win[1] = CreateTexture("2_win.png");
//
//	Worldbox[0].Tlocate = glm::vec3(0.0f, 0.0f, 8.0f);
//	Worldbox[1].Tlocate = glm::vec3(8.0f, 0.0f, 0.0f);
//	Worldbox[2].Tlocate = glm::vec3(0.0f, 0.0f, -8.0f);
//	Worldbox[3].Tlocate = glm::vec3(-8.0f, 0.0f, 0.0f);
//
//	for (int i = 0; i < 4; i++) {
//		Worldbox[i].Tscale = glm::vec3(20.0f, 15.0f, 20.0f);
//		Worldbox[i].Trotate = 90 * i;
//		Worldbox[i].Ttr = glm::mat4(1.0f);
//		glm::mat4 Tx = glm::mat4(1.0f);
//		glm::mat4 Scale = glm::mat4(1.0f);
//		glm::mat4 Rotate = glm::mat4(1.0f);
//		Scale = glm::scale(Scale, glm::vec3(Worldbox[i].Tscale)); //		각 사각형 크기 
//		Rotate = glm::rotate(Rotate, glm::radians(float(Worldbox[i].Trotate)), glm::vec3(0.0, 1.0, 0.0));
//		Tx = glm::translate(Tx, Worldbox[i].Tlocate);
//		Worldbox[i].Ttr = Tx * Rotate * Scale * Worldbox[i].Ttr;
//	}
//}
// 여기까지


int collide(Player* p, Box b, glm::mat4 TR)
{

	glm::vec4 a1 = TR * glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f);                    // 플레이어 왼,오른,앞,뒤  원래 좌표를 각각 vec로 저장
	glm::vec4 a2 = TR * glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	glm::vec4 a3 = TR * glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f);
	glm::vec4 a4 = TR * glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);

	glm::vec4 player_bounding_box[2] = { a1, a2 }; // 0이 min, 1이 max

	if ((player_bounding_box[0][0] <= b.Bounding_box[1][0] && player_bounding_box[0][0] >= b.Bounding_box[0][0] && player_bounding_box[0][2] >= b.Bounding_box[0][2] && player_bounding_box[0][2] <= b.Bounding_box[1][2]) ||
		(player_bounding_box[0][0] <= b.Bounding_box[1][0] && player_bounding_box[0][0] >= b.Bounding_box[0][0] && player_bounding_box[1][2] >= b.Bounding_box[0][2] && player_bounding_box[1][2] <= b.Bounding_box[1][2]) ||
		(player_bounding_box[1][0] <= b.Bounding_box[1][0] && player_bounding_box[1][0] >= b.Bounding_box[0][0] && player_bounding_box[1][2] >= b.Bounding_box[0][2] && player_bounding_box[1][2] <= b.Bounding_box[1][2]) ||
		(player_bounding_box[1][0] <= b.Bounding_box[1][0] && player_bounding_box[1][0] >= b.Bounding_box[0][0] && player_bounding_box[0][2] >= b.Bounding_box[0][2] && player_bounding_box[0][2] <= b.Bounding_box[1][2]) &&
		(player_bounding_box[0][1] <= b.Bounding_box[1][1] && player_bounding_box[1][1] >= b.Bounding_box[0][1])) {
		return b.offset;
	}

	return -1;
}

void Crash(int num, int inspection)
{
	/*if (All_Box[inspection / 20][inspection % 20].Bcolor != player[num].Get_Color()) {
		if (All_Box[inspection / 20][inspection % 20].Bcolor != glm::vec3{ 0.0f,0.0f,0.0f }) {
			if (num == 0)
				player[1].Add_Occupy(-1);
			else
				player[0].Add_Occupy(-1);
		}
		All_Box[inspection / 20][inspection % 20].Bcolor = player[num].Get_Color();
		player[num].Add_Occupy(+1);
	}*/
	//player[num].gravity = 0;
}

// 타임을 그려주는 함수
void Draw_time() {
	//glUseProgram(triangleShaderProgramID);
	//glBindVertexArray(triangleVertexArrayObject);

	//glUniform1i(glGetUniformLocation(triangleShaderProgramID, "tex"), 0);

	//glm::mat4 projection = glm::mat4(1.0f);
	//unsigned int projectionLocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//glm::mat4 view = glm::mat4(1.0f);
	//unsigned int viewLocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	//glActiveTexture(GL_TEXTURE0);						// 뒷자리 숫자
	//glBindTexture(GL_TEXTURE_2D, texureId[int(Now_time) % 10]);
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Timecount[0].Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindTexture(GL_TEXTURE_2D, texureId[int(Now_time) / 10]);			// 앞자리 숫자
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Timecount[1].Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Draw_num(int num) {
	//glUseProgram(triangleShaderProgramID);
	//glBindVertexArray(triangleVertexArrayObject);

	//glUniform1i(glGetUniformLocation(triangleShaderProgramID, "tex"), 0);

	//glm::mat4 projection = glm::mat4(1.0f);
	//unsigned int projectionLocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//glm::mat4 view = glm::mat4(1.0f);
	//unsigned int viewLocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	//glActiveTexture(GL_TEXTURE0);						// 뒷자리 숫자
	//glBindTexture(GL_TEXTURE_2D, texureId[int(num / 100)]);
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Score[0].Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindTexture(GL_TEXTURE_2D, texureId[int(num / 10) % 10]);			// 앞자리 숫자
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Score[1].Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindTexture(GL_TEXTURE_2D, texureId[num % 10]);			// 앞자리 숫자
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Score[2].Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Logo_state() {
	//glUseProgram(triangleShaderProgramID);
	//glBindVertexArray(triangleVertexArrayObject);

	//glUniform1i(glGetUniformLocation(triangleShaderProgramID, "tex"), 0);

	//glm::mat4 projection = glm::mat4(1.0f);
	//unsigned int projectionLocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//glm::mat4 view = glm::mat4(1.0f);
	//unsigned int viewLocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Logo_texture.Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glActiveTexture(GL_TEXTURE0);						// 뒷자리 숫자
	//glBindTexture(GL_TEXTURE_2D, Logo);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	//glViewport(0,0,1260,700);
}

void Whos_win() {
	//glUseProgram(triangleShaderProgramID);
	//glBindVertexArray(triangleVertexArrayObject);

	//glUniform1i(glGetUniformLocation(triangleShaderProgramID, "tex"), 0);

	//glm::mat4 projection = glm::mat4(1.0f);
	//unsigned int projectionLocation = glGetUniformLocation(triangleShaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//glm::mat4 view = glm::mat4(1.0f);
	//unsigned int viewLocation = glGetUniformLocation(triangleShaderProgramID, "viewTransform");
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Logo_texture.Ttr)); //--- modelTransform 변수에 변환 값 적용하기
	//glActiveTexture(GL_TEXTURE0);						// 뒷자리 숫자
	////if(player[0].Occupy_box>player[1].Occupy_box)
	////	glBindTexture(GL_TEXTURE_2D, Who_win[0]);
	////else
	//	glBindTexture(GL_TEXTURE_2D, Who_win[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Create_item() {
	//srand(time(NULL));

	//glm::vec3 bound_scale = { 0.3f / 2, yScale, 0.3f / 2 };

	//for (int i = 0; i < 20; i++) {
	//	int x = rand() % 20;
	//	int y = rand() % 20;
	//	item[i].Ilocate = All_Box[x][y].Blocate;
	//	item[i].Iscale = glm::vec3{0.3f,0.3f,0.3f};
	//	item[i].Ilocate[1] =  0.0f;
	//	item[i].Item_type = rand()%2;
	//	
	//	if (item[i].Item_type == 0)
	//		item[i].Icolor = glm::vec3{ 1.0f,0.0f,1.0f };
	//	else if (item[i].Item_type == 1)
	//		item[i].Icolor = glm::vec3{ 1.0f,1.0f,1.0f };

	//	glm::mat4 TR = glm::mat4(1.0f);
	//	glm::mat4 Tx = glm::mat4(1.0f);
	//	glm::mat4 Scale = glm::mat4(1.0f);

	//	Scale = glm::scale(Scale, glm::vec3(item[i].Iscale)); //		각 사각형 크기 
	//	Tx = glm::translate(Tx, item[i].Ilocate);

	//	item[i].TR = Tx * Scale * TR;

	//	item[i].Bounding_box[0] = {(item[i].Ilocate - bound_scale), 1.f};
	//	item[i].Bounding_box[1] = { (item[i].Ilocate + bound_scale), 1.f };

	//	

	//	item[i].View = false;
	//}
}

int item_collide(Player* p, Item i, glm::mat4 TR)
{
	//glm::vec4 a1 = TR * glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f);                    // 플레이어 왼,오른,앞,뒤  원래 좌표를 각각 vec로 저장
	//glm::vec4 a2 = TR * glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	//glm::vec4 a3 = TR * glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f);
	//glm::vec4 a4 = TR * glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);

	//glm::vec4 player_bounding_box[2] = { a1, a2 }; // 0이 min, 1이 max

	//if ((player_bounding_box[0][0] <= i.Bounding_box[1][0] && player_bounding_box[0][0] >= i.Bounding_box[0][0] && player_bounding_box[0][2] >= i.Bounding_box[0][2] && player_bounding_box[0][2] <= i.Bounding_box[1][2]) ||
	//	(player_bounding_box[0][0] <= i.Bounding_box[1][0] && player_bounding_box[0][0] >= i.Bounding_box[0][0] && player_bounding_box[1][2] >= i.Bounding_box[0][2] && player_bounding_box[1][2] <= i.Bounding_box[1][2]) ||
	//	(player_bounding_box[1][0] <= i.Bounding_box[1][0] && player_bounding_box[1][0] >= i.Bounding_box[0][0] && player_bounding_box[1][2] >= i.Bounding_box[0][2] && player_bounding_box[1][2] <= i.Bounding_box[1][2]) ||
	//	(player_bounding_box[1][0] <= i.Bounding_box[1][0] && player_bounding_box[1][0] >= i.Bounding_box[0][0] && player_bounding_box[0][2] >= i.Bounding_box[0][2] && player_bounding_box[0][2] <= i.Bounding_box[1][2])) {
	//	//return p->player_number;
	//}
	//return -1;
	return -1;
}

void Item_zero(Player* p, Item i) {
	int enermy = 0;
	//if (p->player_number == 0) {
	enermy = 1;
	//}
	//else {
	enermy = 0;
	//}
	//player[enermy].stop = true;
	//player[enermy].timer = Now_time;
	//player[enermy].x = 0;
	//player[enermy].z = 0;
}

void Item_one(Player* p, Item i) {
	//srand(time(NULL));
	//for (int i = 0; i < 2; i++) {
	//	int indexX = rand() % 20;
	//	int indexY = rand() % 20;
	//	if (All_Box[indexX][indexY].Bcolor != p->PColor) {
	//		if (All_Box[indexX][indexY].Bcolor != glm::vec3{ 0.0f,0.0f,0.0f }) {
	//			if (p->player_number == 0)
	//				player[1].Occupy_box -= 1;
	//			else
	//				player[0].Occupy_box -= 1;
	//		}
	//		All_Box[indexX][indexY].Bcolor = p->PColor;
	//		p->Occupy_box += 1;
	//	}
	//	else
	//		i -= 1;
	//}
}

void init() {
	//Create_item();
	start_time = time(NULL);
	Creat_time = time(NULL);
	Game_over = false;
	Itemcount = 0;
}