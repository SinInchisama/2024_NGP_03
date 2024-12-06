#pragma comment(lib, "lib/freeglut.lib")
#pragma comment(lib, "lib/Freeimage.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")
//1111
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
#include "CTimer.h"
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
	glutTimerFunc(50, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid KeyDownboard(unsigned char key, int x, int y) {
	FrameWork::currentInstance->KeyDownboard(key,x,y);
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

