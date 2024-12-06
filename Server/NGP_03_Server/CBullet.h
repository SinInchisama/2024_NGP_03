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
	float dist;

	glm::vec4 Bounding_box[2];

	bool View;

	Bullet()
		: Bscale(0.3f, 0.3f, 0.3f),   // 기본 크기 1
		Blocate(0.0f, 0.0f, 0.0f), // 기본 위치 (0, 0, 0)
		Bcolor(0.7f, 0.0f, 0.7f),  // 기본 색상 흰색
		TR(1.0f),                  // 기본 변환 행렬 (단위 행렬)
		x_dir(0),                  // 기본 방향 0
		z_dir(0),                  // 기본 방향 0
		speed(0.15f),               // 기본 속도 0
		Bounding_box{ glm::vec4(0.0f), glm::vec4(0.0f) }, // 기본 Bounding Box
		View(false),                // 기본적으로 보이지 않음
		dist(4.0f)
	{
		glm::mat4 TR1 = glm::mat4(1.0f);
		glm::mat4 Scale = glm::mat4(1.0f);

		Scale = glm::scale(Scale, Bscale); //		플레이어
		TR = Scale * TR1;
	}

	void InitBullet(byte index, glm::vec3 locate, byte b);
	void Move(int i);

	void serializeBullet(char* buffer) const;
	void deserializeBullet(const char* buffer);
};
