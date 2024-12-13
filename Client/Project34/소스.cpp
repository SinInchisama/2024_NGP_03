#pragma comment(lib, "lib/freeglut.lib")
#pragma comment(lib, "lib/Freeimage.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")
#include <random>

#include <iostream>
#include "include/GL/glew.h" // �ʿ��� ������� include
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

GLUquadricObj* qobj = gluNewQuadric();

FrameWork* FrameWork::currentInstance = nullptr;


int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1260, 700);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	FrameWork framework;  // ���� ������ FrameWork ��ü ����
	FrameWork::currentInstance = &framework;

	//Texture_init();
	glewInit();
	framework.Init_Shader();
	framework.init_Buffer();
	glutDisplayFunc(FrameWork::DisplayWrapper);
	glutReshapeFunc(FrameWork::DisplayReShape);
	glutKeyboardFunc(KeyDownboard); // Ű���� �Է� �ݹ��Լ� ����
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
