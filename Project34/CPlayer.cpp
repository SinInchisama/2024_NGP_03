#include "CPlayer.h"

void Player::Calculate_Move()
{
	int x = 0, z = 0;
	if (Action & KEY_UP) {
		z -= 1;
	}
	if (Action & KEY_DOWN) {
		z += 1;
	}
	if (Action & KEY_LEFT) {
		x -= 1;
	}
	if (Action & KEY_RIGHT) {
		x += 1;
	}
	Move[0] += cos(glm::radians(lotate)) * speed * x;			// 플레이어 좌우 움직임 할때 쓰는 계산
	Move[2] += sin(glm::radians(lotate)) * speed * x;
	Move[0] += sin(glm::radians(lotate)) * speed * z;			// 플레이어 위 아래 움직임 할때 쓰는 계산
	Move[2] += cos(glm::radians(lotate)) * speed * z;
}

void Player::Calculate_Camera()
{
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);
	glm::mat4 Rotate = glm::mat4(1.0f);

	Rotate = glm::rotate(Rotate, glm::radians(lotate), glm::vec3(0.0, 1.0, 0.0));
	Scale = glm::scale(Scale, Pscale); //		플레이어
	Tx = glm::translate(Tx, Plocate + Move);
	TR = Tx * Rotate * Scale * TR;

	cameraPos = TR * glm::vec4(0.0f, 15.0f, 0.0f, 1.0f);
	cameraDirection = glm::vec3(0.0f, 0.5f, -1.0f);

	cameraDirection[0] = sin(glm::radians(lotate)) * -1.0;
	cameraDirection[2] = cos(glm::radians(lotate)) * -1.0;
}
