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

void Player::serializePlayer(char* buffer) const
{
    int offset = 0;

    // 각 변수들을 buffer에 복사
    memcpy(buffer + offset, &Pscale, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &Plocate, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &PColor, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &Color, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &Move, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &cameraPos, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &cameraDirection, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(buffer + offset, &gravity, sizeof(float));
    offset += sizeof(float);

    memcpy(buffer + offset, &lotate, sizeof(float));
    offset += sizeof(float);

    memcpy(buffer + offset, &view, sizeof(bool));
    offset += sizeof(bool);

    memcpy(buffer + offset, &Occupy_box, sizeof(int));
    offset += sizeof(int);

    memcpy(buffer + offset, &speed, sizeof(float));
    offset += sizeof(float);

    memcpy(buffer + offset, &left_rotate, sizeof(bool));
    offset += sizeof(bool);

    memcpy(buffer + offset, &right_rotate, sizeof(bool));
    offset += sizeof(bool);

    memcpy(buffer + offset, &player_number, sizeof(int));
    offset += sizeof(int);

    memcpy(buffer + offset, &stop, sizeof(bool));
    offset += sizeof(bool);

    memcpy(buffer + offset, &Action, sizeof(byte));
    offset += sizeof(byte);

    memcpy(buffer + offset, &timer, sizeof(int));
}

void Player::deserializePlayer(const char* buffer)
{
    int offset = 0;

    memcpy(&Pscale, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&Plocate, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&PColor, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&Color, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&Move, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&cameraPos, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&cameraDirection, buffer + offset, sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy(&gravity, buffer + offset, sizeof(float));
    offset += sizeof(float);

    memcpy(&lotate, buffer + offset, sizeof(float));
    offset += sizeof(float);

    memcpy(&view, buffer + offset, sizeof(bool));
    offset += sizeof(bool);

    memcpy(&Occupy_box, buffer + offset, sizeof(int));
    offset += sizeof(int);

    memcpy(&speed, buffer + offset, sizeof(float));
    offset += sizeof(float);

    memcpy(&left_rotate, buffer + offset, sizeof(bool));
    offset += sizeof(bool);

    memcpy(&right_rotate, buffer + offset, sizeof(bool));
    offset += sizeof(bool);

    memcpy(&player_number, buffer + offset, sizeof(int));
    offset += sizeof(int);

    memcpy(&stop, buffer + offset, sizeof(bool));
    offset += sizeof(bool);

    memcpy(&Action, buffer + offset, sizeof(byte));
    offset += sizeof(byte);

    memcpy(&timer, buffer + offset, sizeof(int));

}