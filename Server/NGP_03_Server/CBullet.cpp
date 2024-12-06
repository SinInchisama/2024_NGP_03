#include "CBullet.h"

void Bullet::InitBullet(byte index, glm::vec3 locate,byte b)
{
	glm::vec3 bound_scale = { 0.1f / 2, 0.1f / 2, 0.1f / 2 };

	Move1 = locate;

	glm::mat4 TR1 = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	Scale = glm::scale(Scale, glm::vec3(Bscale));
	Tx = glm::translate(Tx, Move1);

	TR1 = Tx * Scale * TR;

	Bounding_box[0] = { (Blocate - bound_scale), 1.f };
	Bounding_box[1] = { (Blocate + bound_scale), 1.f };

	Move1 = locate;

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

void Bullet::Move(int i)
{
	Move1[0] += cos(glm::radians(180.0f * i)) * speed*x_dir;			// �÷��̾� �¿� ������ �Ҷ� ���� ���
	Move1[2] += sin(glm::radians(180.0f * i)) * speed * x_dir;
	Move1[0] += sin(glm::radians(180.0f * i)) * speed * z_dir;			// �÷��̾� �� �Ʒ� ������ �Ҷ� ���� ���
	Move1[2] += cos(glm::radians(180.0f * i)) * speed * z_dir;
}

void Bullet::serializeBullet(char* buffer) const
{
	int offset = 0;

	// glm::vec3 ���
	memcpy(buffer + offset, &Bscale, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(buffer + offset, &Blocate, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(buffer + offset, &Bcolor, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

	// glm::mat4 TR
	memcpy(buffer + offset, glm::value_ptr(TR), sizeof(glm::mat4)); offset += sizeof(glm::mat4);

	// byte ���
	memcpy(buffer + offset, &x_dir, sizeof(byte)); offset += sizeof(byte);
	memcpy(buffer + offset, &z_dir, sizeof(byte)); offset += sizeof(byte);

	// float ���
	memcpy(buffer + offset, &speed, sizeof(float)); offset += sizeof(float);

	// glm::vec4 �迭
	memcpy(buffer + offset, Bounding_box, sizeof(glm::vec4) * 2); offset += sizeof(glm::vec4) * 2;

	// bool View
	memcpy(buffer + offset, &View, sizeof(bool)); offset += sizeof(bool);

}

void Bullet::deserializeBullet(const char* buffer)
{
	int offset = 0;

	// glm::vec3 ���
	memcpy(&Bscale, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(&Blocate, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(&Bcolor, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

	// glm::mat4 TR
	memcpy(glm::value_ptr(TR), buffer + offset, sizeof(glm::mat4)); offset += sizeof(glm::mat4);

	// byte ���
	memcpy(&x_dir, buffer + offset, sizeof(byte)); offset += sizeof(byte);
	memcpy(&z_dir, buffer + offset, sizeof(byte)); offset += sizeof(byte);

	// float ���
	memcpy(&speed, buffer + offset, sizeof(float)); offset += sizeof(float);

	// glm::vec4 �迭
	memcpy(Bounding_box, buffer + offset, sizeof(glm::vec4) * 2); offset += sizeof(glm::vec4) * 2;

	// bool View
	memcpy(&View, buffer + offset, sizeof(bool)); offset += sizeof(bool);

}
