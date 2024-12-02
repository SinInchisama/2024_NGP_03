#include "CBullet.h"

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