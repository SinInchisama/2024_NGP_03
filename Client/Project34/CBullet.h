#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

class Bullet {
public:
	glm::vec3 Bscale;
	glm::vec3 Blocate;
	glm::vec3 Bcolor;
	glm::mat4 TR;

	byte x_dir;
	byte z_dir;
	float speed;

	glm::vec4 Bounding_box[2];

	bool View;

	Bullet()
		: Bscale(0.1f, 0.1f, 0.1f),   // �⺻ ũ�� 1
		Blocate(0.0f, 0.0f, 0.0f), // �⺻ ��ġ (0, 0, 0)
		Bcolor(0.7f, 0.0f, 0.7f),  // �⺻ ���� ���
		TR(1.0f),                  // �⺻ ��ȯ ��� (���� ���)
		x_dir(0),                  // �⺻ ���� 0
		z_dir(0),                  // �⺻ ���� 0
		speed(0.15f),               // �⺻ �ӵ� 0
		Bounding_box{ glm::vec4(0.0f), glm::vec4(0.0f) }, // �⺻ Bounding Box
		View(false)                // �⺻������ ������ ����
	{
		glm::mat4 TR1 = glm::mat4(1.0f);
		glm::mat4 Scale = glm::mat4(1.0f);
		glm::mat4 Rotate = glm::mat4(1.0f);

		Rotate = glm::rotate(Rotate, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
		Scale = glm::scale(Scale, Bscale); //		�÷��̾�
		TR = Rotate * Scale * TR1;
	}

	void serializeBullet(char* buffer) const;
	void deserializeBullet(const char* buffer);
};

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
