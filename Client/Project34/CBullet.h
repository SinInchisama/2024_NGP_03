#pragma once
#include "include/glm/glm.hpp"

class Bullet {
public:
	glm::vec3 Iscale;
	glm::vec3 Ilocate;
	glm::vec3 Icolor;
	//glm::mat4 TR;

	int x, y, z;
	bool enable{ false };

	glm::vec4 Bounding_box[2];

	bool View;
};
// �ҽ�.cpp ���Ͽ� �÷��̾� �� �迭 ����
// �迭�� �ε����� �Ѿ��� ���� (�÷��̾ ���� �Ѿ� ���� ���� �߰� �ʿ�?)
// ���� Ȱ��ȭ �ÿ� ����� �ӷ��� �������� �� Ȱ��ȭ (���� �Ѿ��� �ӷ��� �����Ǿ� �ִٸ�, ������ �Բ� �ʱ�ȭ�ϵ��� ����)
// �Ѿ��� ���� ������ ���� �����Ǵ� ���� ���� �ʿ�