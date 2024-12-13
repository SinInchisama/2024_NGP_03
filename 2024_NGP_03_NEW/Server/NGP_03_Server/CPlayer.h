#pragma once
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Public.h"
#include <bitset>
#include "FunctionalPackets.h"

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

		glm::mat4 TR1 = glm::mat4(1.0f);
		glm::mat4 Scale = glm::mat4(1.0f);
		glm::mat4 Rotate = glm::mat4(1.0f);

		Rotate = glm::rotate(Rotate, glm::radians(lotate), glm::vec3(0.0, 1.0, 0.0));
		Scale = glm::scale(Scale, Pscale); //		플레이어
		TR = Rotate * Scale * TR1;

		Action = 0;
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
	glm::mat4 Get_TR() { return TR; }
	byte Get_Action() { return Action; }
	short Get_Box() { return Occupy_box; }

	void Set_UpAction(KeyInput key) {
		Action &= ~key;  }
	void Set_DownAction(KeyInput key) {
		Action|= key;
	}
	void Set_Action(byte key) {
		Action = key;
	}

	void Set_Plocate(glm::vec3 v) {Plocate = v;}

	void Add_Occupy(int x) {Occupy_box += x;}

	void Calculate_Move();
	void Calculate_Camera();

	void serializePlayer(char* buffer) const;
	void deserializePlayer(const char* buffer);

	byte whoWin(Player& p) { return Occupy_box < p.Get_Box(); };
};