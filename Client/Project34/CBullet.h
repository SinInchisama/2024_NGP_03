#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

class Bullet {
public:
	glm::vec3 Bscale;
	glm::vec3 Blocate;
	glm::vec3 Bcolor;
	glm::mat4 TR;

	int x, y, z;
	int x_dir;
	int z_dir;
	float speed;

	glm::vec4 Bounding_box[2];

	bool View;
};

<<<<<<< HEAD
void InitBullet(Bullet& bullet)
{
	glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };
=======
void InitBullet(Bullet& bullet);

	//glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };
>>>>>>> 김선빈

	int x = rand() % 20;
	int z = rand() % 20;
	// �Ѿ��� ��ǥ�� �ӽ÷� 0, 0, 0���� �ʱ�ȭ. 
	// �Ѿ��� Ȱ��ȭ�� �� �Ѿ��� �߻��� �÷��̾��� ��ġ�� ������� �ٲ���� ��.
	bullet.Blocate = glm::vec3{ 0.0f, 0.0f, 0.0f };
	// �ϴ� �Ѿ��� ũ�⸦ item�� ���� ����. 
	bullet.Bscale = glm::vec3{ 0.3f,0.3f,0.3f };

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	Scale = glm::scale(Scale, glm::vec3(bullet.Bscale)); //		�� �簢�� ũ�� 
	Tx = glm::translate(Tx, bullet.Blocate);

	bullet.TR = Tx * Scale * TR;

	bullet.Bounding_box[0] = { (bullet.Blocate - bound_scale), 1.f };
	bullet.Bounding_box[1] = { (bullet.Blocate + bound_scale), 1.f };

	// �Ѿ��� ������ 0, 0���� �ʱ�ȭ. 
	// �Ѿ��� Ȱ��ȭ�� �� �Ѿ��� �߻��� �÷��̾ �ٶ󺸴� ������ ������� �ٲ���� ��. 
	bullet.x_dir = 0;
	bullet.z_dir = 0;

	// �ϴ� Player�� 3�� �ӵ��� �� ����. �ʿ��ϴٸ� ������ ��. 
	bullet.speed = 0.15f;

<<<<<<< HEAD
	bullet.View = false;
}
=======
	//bullet.View = false;
>>>>>>> 김선빈
