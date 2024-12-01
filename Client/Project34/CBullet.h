#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"
#include "CPlayer.h"

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