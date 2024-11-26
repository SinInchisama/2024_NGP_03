#pragma once
#include "include/glm/glm.hpp"

class Bullet {
private:
	int dir_x, dir_y;
	float speed;

public:
	glm::vec3 Iscale;
	glm::vec3 Ilocate;
	glm::vec3 Icolor;
	//glm::mat4 TR;

	int x, y, z;
	bool enable{ false };

	glm::vec4 Bounding_box[2];

	bool View;

	void set_dir(int _dir_x, int _dir_y) 
	{
		dir_x = _dir_x;
		dir_y = _dir_y;
	}

	void set_speed(float _speed) 
	{
		speed = _speed;
	}

	void move() 
	{
		x += speed * dir_x;
		y += speed * dir_y;
	}
};
// �ҽ�.cpp ���Ͽ� �÷��̾� �� �迭 ����
// �迭�� �ε����� �Ѿ��� ���� (�÷��̾ ���� �Ѿ� ���� ���� �߰� �ʿ�?)
// ���� Ȱ��ȭ �ÿ� ����� �ӷ��� �������� �� Ȱ��ȭ (���� �Ѿ��� �ӷ��� �����Ǿ� �ִٸ�, ������ �Բ� �ʱ�ȭ�ϵ��� ����)
// �Ѿ��� ���� ������ ���� �����Ǵ� ���� ���� �ʿ�