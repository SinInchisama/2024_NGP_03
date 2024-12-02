#pragma once
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Public.h"

class Bullet {
public:
	glm::vec3 Bscale;
	glm::vec3 Blocate;
	glm::vec3 Bcolor;
	glm::vec3 Move1;
	glm::mat4 TR;

	int x_dir;
	int z_dir;
	float speed;

	glm::vec4 Bounding_box[2];

	bool View;

	Bullet();

	void InitBullet(byte& index, glm::vec3 locate, byte& b);
	void Move();

	void serializeBullet(char* buffer) const;
	void deserializeBullet(const char* buffer);
};

//void InitBullet(Bullet& bullet)
//{
//	glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };
//
//	int x = rand() % 20;
//	int z = rand() % 20;
//	// �Ѿ��� ��ǥ�� �ӽ÷� 0, 0, 0���� �ʱ�ȭ. 
//	// �Ѿ��� Ȱ��ȭ�� �� �Ѿ��� �߻��� �÷��̾��� ��ġ�� ������� �ٲ���� ��.
//	bullet.Blocate = glm::vec3{ 0.0f, 0.0f, 0.0f };
//	// �ϴ� �Ѿ��� ũ�⸦ item�� ���� ����. 
//	bullet.Bscale = glm::vec3{ 0.3f,0.3f,0.3f };
//
//	glm::mat4 TR = glm::mat4(1.0f);
//	glm::mat4 Tx = glm::mat4(1.0f);
//	glm::mat4 Scale = glm::mat4(1.0f);
//
//	Scale = glm::scale(Scale, glm::vec3(bullet.Bscale)); //		�� �簢�� ũ�� 
//	Tx = glm::translate(Tx, bullet.Blocate);
//
//	bullet.TR = Tx * Scale * TR;
//
//	bullet.Bounding_box[0] = { (bullet.Blocate - bound_scale), 1.f };
//	bullet.Bounding_box[1] = { (bullet.Blocate + bound_scale), 1.f };
//
//	// �Ѿ��� ������ 0, 0���� �ʱ�ȭ. 
//	// �Ѿ��� Ȱ��ȭ�� �� �Ѿ��� �߻��� �÷��̾ �ٶ󺸴� ������ ������� �ٲ���� ��. 
//	bullet.x_dir = 0;
//	bullet.z_dir = 0;
//
//	// �ϴ� Player�� 3�� �ӵ��� �� ����. �ʿ��ϴٸ� ������ ��. 
//	bullet.speed = 0.15f;
//
//	bullet.View = false;
//}
//
//void Bullet::serializeBullet(char* buffer) const
//{
//	// Serialize glm::vec3 Color (3 floats)
//	memcpy(buffer, &Bcolor, sizeof(Bcolor));
//	buffer += sizeof(Bcolor);
//
//	// Serialize glm::mat4 TR (16 floats)
//	memcpy(buffer, &TR, sizeof(TR));
//	buffer += sizeof(TR);
//
//	// Serialize glm::vec4 Bounding_box (2 vec4s)
//	memcpy(buffer, &Bounding_box, sizeof(Bounding_box));
//
//	// Serialize int x_dir
//	memcpy(buffer, &x_dir, sizeof(x_dir));
//	buffer += sizeof(x_dir);
//
//	// Serialize int z_dir
//	memcpy(buffer, &z_dir, sizeof(z_dir));
//	buffer += sizeof(z_dir);
//
//	// Serialize float speed
//	memcpy(buffer, &speed, sizeof(speed));
//	buffer += sizeof(speed);
//}
//
//void Bullet::deserializeBullet(const char* buffer)
//{
//	// Deserialize glm::vec3 Color (3 floats)
//	memcpy(&Bcolor, buffer, sizeof(Bcolor));
//	buffer += sizeof(Bcolor);
//
//	// Deserialize glm::mat4 TR (16 floats)
//	memcpy(&TR, buffer, sizeof(TR));
//	buffer += sizeof(TR);
//
//	// Deserialize glm::vec4 Bounding_box (2 vec4s)
//	memcpy(&Bounding_box, buffer, sizeof(Bounding_box));
//
//	// Deserialize int x_dir
//	memcpy(&x_dir, buffer, sizeof(x_dir));
//	buffer += sizeof(x_dir);
//
//	// Deserialize int z_dir
//	memcpy(&z_dir, buffer, sizeof(z_dir));
//	buffer += sizeof(z_dir);
//
//	// Deserialize float speed
//	memcpy(&speed, buffer, sizeof(speed));
//	buffer += sizeof(speed);
//}