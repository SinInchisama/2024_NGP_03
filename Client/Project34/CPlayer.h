#pragma once
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Public.h"
#include <bitset>
#include "CBullet.h"

class Player
{
private:
	glm::vec3 Pscale;
	glm::vec3 Plocate;
	glm::vec3 PColor;
	glm::vec3 Color;
	glm::vec3 Move;
	glm::mat4 TR;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;

	float gravity;
	float lotate;
	bool view;

	short Occupy_box;
	float speed;

	byte player_number;  //캐릭터 고유 숫자 1p, 2p
	bool stop; //시계 효과를 받았을 경우 true

	byte Action = 0;

	//Bullet bullet;

	int timer;

public:
	Player(int i, glm::vec3 initialLocation) {
		gravity = 0.05f;
		PColor = { 1.0f, 1.0f * i, 0.0f };
		Color = { 0.5f, 1.0f * i, 0.3f * i };
		Plocate = initialLocation;
		Plocate[1] = 0.0f; // Y 좌표 설정
		Pscale = { 0.2f, 0.2f, 0.2f };
		lotate = 180.0f * i;
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
	byte Get_Action() { return Action; }

	glm::mat4 Get_TR() { return TR; }

	void Set_UpAction(KeyInput key) {
		Action &= ~key;  }
	void Set_DownAction(KeyInput key) {
		Action|= key;
	}
	void Set_Action(KeyInput key) {
		Action = key;
	}

	void Set_Plocate(glm::vec3 v) {Plocate = v;}
	void Set_Move(glm::vec3 v) { Move = v; }

	void Add_Occupy(int x) {Occupy_box += x;}

	void Calculate_Move();
	void Calculate_Camera();

	void serializePlayer(char* buffer) const;
	void deserializePlayer(const char* buffer);
};

