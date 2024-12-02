#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

class Bullet {
private:
	glm::vec3 Bscale;
	glm::vec3 Blocate;
	glm::vec3 Bcolor;
	glm::mat4 TR;

	glm::vec3 Color;
	glm::vec3 Move;

	int x, y, z;
	int x_dir;
	int z_dir;
	float speed;

	float lotate;

	int player_number; // �÷��̾� ���� ����

	glm::vec4 Bounding_box[2];

	bool View;

	byte Action = 0;

public:
	Bullet(int i, glm::vec3 initialLocation) {
		Bcolor = { 1.0f, 1.0f * i, 0.0f };
		Color = { 0.5f, 1.0f * i, 0.3f * i };
		Blocate = initialLocation;
		Blocate[1] = 0.0f; // Y ��ǥ ����
		Bscale = { 0.2f, 0.2f, 0.2f };
		lotate = 180.0f * i;
		speed = 0.05f;
		player_number = i;
		Move = { 0.0f, 0.0f, 0.0f };
	}

	glm::vec3 Get_Pscale() { return Bscale; }
	glm::vec3 Get_Plocate() { return Blocate; }
	glm::vec3 Get_Move() { return Move; }
	glm::vec3 Get_Color() { return Bcolor; }
	GLfloat Get_R() { return Color[0]; }
	GLfloat Get_G() { return Color[1]; }
	GLfloat Get_B() { return Color[2]; }
	float Get_Lotate() { return lotate; }
	byte Get_Action() { return Action; }

	void Calculate_Move();
};

void InitBullet(Bullet& bullet);

	//glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };

	//int x = rand() % 20;
	//int z = rand() % 20;
	//// �Ѿ��� ��ǥ�� �ӽ÷� 0, 0, 0���� �ʱ�ȭ. 
	//// �Ѿ��� Ȱ��ȭ�� �� �Ѿ��� �߻��� �÷��̾��� ��ġ�� ������� �ٲ���� ��.
	//bullet.Blocate = glm::vec3{ 0.0f, 0.0f, 0.0f };
	//// �ϴ� �Ѿ��� ũ�⸦ item�� ���� ����. 
	//bullet.Bscale = glm::vec3{ 0.3f,0.3f,0.3f };

	//glm::mat4 TR = glm::mat4(1.0f);
	//glm::mat4 Tx = glm::mat4(1.0f);
	//glm::mat4 Scale = glm::mat4(1.0f);

	//Scale = glm::scale(Scale, glm::vec3(bullet.Bscale)); //		�� �簢�� ũ�� 
	//Tx = glm::translate(Tx, bullet.Blocate);

	//bullet.TR = Tx * Scale * TR;

	//bullet.Bounding_box[0] = { (bullet.Blocate - bound_scale), 1.f };
	//bullet.Bounding_box[1] = { (bullet.Blocate + bound_scale), 1.f };

	//// �Ѿ��� ������ 0, 0���� �ʱ�ȭ. 
	//// �Ѿ��� Ȱ��ȭ�� �� �Ѿ��� �߻��� �÷��̾ �ٶ󺸴� ������ ������� �ٲ���� ��. 
	//bullet.x_dir = 0;
	//bullet.z_dir = 0;

	//// �ϴ� Player�� 3�� �ӵ��� �� ����. �ʿ��ϴٸ� ������ ��. 
	//bullet.speed = 0.15f;

	//bullet.View = false;
