#include "CBullet.h"
#include "GameMaanger.h"

Bullet::Bullet()
{
	Bscale = glm::vec3{ 0.3f,0.3f,0.3f };
	speed = 0.15f;
	Bcolor = glm::vec3{ 0.7f,0.0f,0.7f };
}

void Bullet::InitBullet(byte& index, glm::vec3 locate,byte& b)
{
	glm::vec3 bound_scale = { 0.3f / 2, 0.3f / 2, 0.3f / 2 };

	Blocate = locate;

	glm::mat4 TR1 = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	Scale = glm::scale(Scale, glm::vec3(Bscale));
	Tx = glm::translate(Tx, Blocate);

	TR1 = Tx * Scale * TR;

	Bounding_box[0] = { (Blocate - bound_scale), 1.f };
	Bounding_box[1] = { (Blocate + bound_scale), 1.f };

	Move1 = { 0.0f, 0.0f, 0.0f };

	if (b & KEY_UP) {
		z_dir -= 1;
	}
	if (b & KEY_DOWN) {
		z_dir += 1;
	}
	if (b & KEY_LEFT) {
		x_dir -= 1;
	}
	if (b & KEY_RIGHT) {
		x_dir += 1;
	}
	if (!x_dir && !z_dir)
		z_dir -= 1;

	View = true;
}

void Bullet::Move()
{
	//Move1[0] += cos(glm::radians(Blocate)) * speed * x_dir;			// 플레이어 좌우 움직임 할때 쓰는 계산
	//Move1[2] += sin(glm::radians(Blocate)) * speed * x_dir;
	//Move1[0] += sin(glm::radians(Blocate)) * speed * z_dir;			// 플레이어 위 아래 움직임 할때 쓰는 계산
	//Move1[2] += cos(glm::radians(Blocate)) * speed * z_dir;
}

void Bullet::serializeBullet(char* buffer) const
{
	int offset = 0;

	// glm::vec3 Bscale
	memcpy(buffer + offset, &Bscale, sizeof(glm::vec3));			offset += sizeof(glm::vec3);

	memcpy(buffer + offset, &Bcolor, sizeof(glm::vec3));					offset += sizeof(glm::vec3);

	// float speed
	memcpy(buffer + offset, &speed, sizeof(float));					offset += sizeof(float);

}

void Bullet::deserializeBullet(const char* buffer)
{
	int offset = 0;

	// glm::vec3 Bscale
	memcpy(&Bscale, buffer + offset, sizeof(glm::vec3));			offset += sizeof(glm::vec3);

	// glm::vec3 Bcolor
	memcpy(&Bcolor, buffer + offset, sizeof(glm::vec3));			offset += sizeof(glm::vec3);

	// float speed
	memcpy(&speed, buffer + offset, sizeof(float));					offset += sizeof(float);

}
