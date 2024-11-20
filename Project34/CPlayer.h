#pragma once
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

class Player
{
private:
	glm::vec3 Pscale;
	glm::vec3 Plocate;
	glm::vec3 PColor;
	glm::vec3 Color;
	glm::vec3 Move;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;

	int x, y, z;
	float gravity;
	float lotate;
	bool view;

	int Occupy_box;
	float speed;

	bool left_rotate;
	bool right_rotate;

	int player_number;  //ĳ���� ���� ���� 1p, 2p
	bool stop; //�ð� ȿ���� �޾��� ��� true

	int timer;

public:
	Player(int i, glm::vec3 initialLocation) {
		gravity = 0.05f;
		PColor = { 1.0f, 1.0f * i, 0.0f };
		Color = { 0.5f, 1.0f * i, 0.3f * i };
		Plocate = initialLocation;
		Plocate[1] = 0.0f; // Y ��ǥ ����
		Pscale = { 0.2f, 0.2f, 0.2f };
		lotate = 180.0f * i;
		x = 0;
		y = 0;
		z = 0;
		gravity = 0.01f;
		speed = 0.05f;
		Occupy_box = 1;
		player_number = i;
		Move = { 0.0f, 0.0f, 0.0f };
	}

	glm::vec3 Get_Pscale() {return Pscale;}
	glm::vec3 Get_Plocate() {return Plocate;}
	glm::vec3 Get_Move() { return Move; }
	glm::vec3 Get_Color() {return PColor;}
	glm::vec3 Get_Camerapos() {return cameraPos;}
	glm::vec3 Get_Cameradirection() {return cameraDirection;}
	GLfloat Get_R() {return Color[0];}
	GLfloat Get_G() { return Color[1]; }
	GLfloat Get_B() { return Color[2]; }
	float Get_Lotate() {return lotate;}

	void Set_X(int i) {x = i;}
	void Set_Y(int i) { y = i; }
	void Set_Z(int i) { z = i; }
	void Set_Plocate(glm::vec3 v) {Plocate = v;}

	void Add_Occupy(int x) {Occupy_box += x;}

	void Calculate_Move();
	void Calculate_Camera();
};

