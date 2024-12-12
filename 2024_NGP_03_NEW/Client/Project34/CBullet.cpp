#include "CBullet.h"
#include "State.h"

void Bullet::serializeBullet(char* buffer) const
{
	int offset = 0;

	// glm::vec3 ¸â¹ö
	memcpy(buffer + offset, &Bscale, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(buffer + offset, &Blocate, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(buffer + offset, &Bcolor, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

	// glm::mat4 TR
	memcpy(buffer + offset, glm::value_ptr(TR), sizeof(glm::mat4)); offset += sizeof(glm::mat4);

	// byte ¸â¹ö
	memcpy(buffer + offset, &x_dir, sizeof(byte)); offset += sizeof(byte);
	memcpy(buffer + offset, &z_dir, sizeof(byte)); offset += sizeof(byte);

	// float ¸â¹ö
	memcpy(buffer + offset, &speed, sizeof(float)); offset += sizeof(float);

	// glm::vec4 ¹è¿­
	memcpy(buffer + offset, Bounding_box, sizeof(glm::vec4) * 2); offset += sizeof(glm::vec4) * 2;

	// bool View
	memcpy(buffer + offset, &View, sizeof(bool)); offset += sizeof(bool);

}

void Bullet::deserializeBullet(const char* buffer)
{
	int offset = 0;

	// glm::vec3 ¸â¹ö
	memcpy(&Bscale, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(&Blocate, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
	memcpy(&Bcolor, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

	// glm::mat4 TR
	memcpy(glm::value_ptr(TR), buffer + offset, sizeof(glm::mat4)); offset += sizeof(glm::mat4);

	// byte ¸â¹ö
	memcpy(&x_dir, buffer + offset, sizeof(byte)); offset += sizeof(byte);
	memcpy(&z_dir, buffer + offset, sizeof(byte)); offset += sizeof(byte);

	// float ¸â¹ö
	memcpy(&speed, buffer + offset, sizeof(float)); offset += sizeof(float);

	// glm::vec4 ¹è¿­
	memcpy(Bounding_box, buffer + offset, sizeof(glm::vec4) * 2); offset += sizeof(glm::vec4) * 2;

	// bool View
	memcpy(&View, buffer + offset, sizeof(bool)); offset += sizeof(bool);

}
