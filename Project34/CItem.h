#pragma once
#include "include/glm/glm.hpp"

class Item {
public:
	int Item_type;	// �� ����

	glm::vec3 Iscale;
	glm::vec3 Ilocate;
	glm::vec3 Icolor;
	glm::mat4 TR;

	glm::vec4 Bounding_box[2];

	bool View;	// boolean check, ����� ���� (437 ~ 445)

	// item_collide �Լ����� item�� ���ڷ� �޴´�. Ȯ�� �ʿ�.
	// item_zero, item_one �Լ����� item�� ���ڷ� �޴´�. Ȯ�� �ʿ�.
};
