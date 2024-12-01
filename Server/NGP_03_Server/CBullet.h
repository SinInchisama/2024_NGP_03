#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

class Player;

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

	void InitBullet(Player& p);
};

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