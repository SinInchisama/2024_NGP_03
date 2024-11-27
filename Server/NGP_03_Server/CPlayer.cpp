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
	Move[0] += cos(glm::radians(lotate)) * speed * x;			// �÷��̾� �¿� ������ �Ҷ� ���� ���
	Move[2] += sin(glm::radians(lotate)) * speed * x;
	Move[0] += sin(glm::radians(lotate)) * speed * z;			// �÷��̾� �� �Ʒ� ������ �Ҷ� ���� ���
	Move[2] += cos(glm::radians(lotate)) * speed * z;
}

void Player::Calculate_Camera()
{
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);
	glm::mat4 Rotate = glm::mat4(1.0f);

	Rotate = glm::rotate(Rotate, glm::radians(lotate), glm::vec3(0.0, 1.0, 0.0));
	Scale = glm::scale(Scale, Pscale); //		�÷��̾�
	Tx = glm::translate(Tx, Plocate + Move);
	TR = Tx * Rotate * Scale * TR;

	cameraPos = TR * glm::vec4(0.0f, 15.0f, 0.0f, 1.0f);
	cameraDirection = glm::vec3(0.0f, 0.5f, -1.0f);

	cameraDirection[0] = sin(glm::radians(lotate)) * -1.0;
	cameraDirection[2] = cos(glm::radians(lotate)) * -1.0;
}

void Player::deserializePlayer(const PlayerData& data)
{
	glm::vec3 temp;

	// glm::vec3 �����͸� ���� (Set �Լ� ���)
	std::memcpy(&temp, data.Pscale, sizeof(temp));
	Pscale = temp;

	std::memcpy(&temp, data.Plocate, sizeof(temp));
	Plocate = temp;

	std::memcpy(&temp, data.PColor, sizeof(temp));
	PColor = temp;

	std::memcpy(&temp, data.Move, sizeof(temp));
	Move = temp;

	std::memcpy(&temp, data.cameraPos, sizeof(temp));
	cameraPos = temp;

	std::memcpy(&temp, data.cameraDirection, sizeof(temp));
	cameraDirection = temp;

	//// ���� ������ ��� ����
	//lotate = data.rotate;
	//Action = data.Action;
	//Occupy_box = data.Occupy_box;
	//view = data.view;
	//speed = data.speed;
	//left_rotate = data.left_rotate;
	//right_rotate = data.right_rotate;
	//player_number = data.player_number;
	//stop = data.stop;
	//timer = data.timer;
}


PlayerData serializePlayer(Player& player)
{
	PlayerData data = {};

	// glm::vec3 �����͸� �迭�� ��ȯ
	glm::vec3 temp;

	temp = player.Get_Pscale();
	std::memcpy(data.Pscale, &temp, sizeof(data.Pscale));

	temp = player.Get_Plocate();
	std::memcpy(data.Plocate, &temp, sizeof(data.Plocate));

	temp = player.Get_Color();
	std::memcpy(data.PColor, &temp, sizeof(data.PColor));

	temp = player.Get_Move();
	std::memcpy(data.Move, &temp, sizeof(data.Move));

	temp = player.Get_Camerapos();
	std::memcpy(data.cameraPos, &temp, sizeof(data.cameraPos));

	temp = player.Get_Cameradirection();
	std::memcpy(data.cameraDirection, &temp, sizeof(data.cameraDirection));

	// ���� ������ ��� ����
	//data.rotate = player.Get_Lotate();
	//data.Action = player.Action; // Action�� ���� ���� ����
	//data.Occupy_box = player.Occupy_box;
	//data.view = player.view;
	//data.speed = player.speed;
	//data.left_rotate = player.left_rotate;
	//data.right_rotate = player.right_rotate;
	//data.player_number = player.player_number;
	//data.stop = player.stop;
	//data.timer = player.timer;

	return data;
}
