#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

class Item {
public:
	int Item_type;	// �� ����

	glm::vec3 IScale;
	glm::vec3 ILocate;
	glm::vec3 Icolor;
	glm::mat4 TR;

	glm::vec4 Bounding_box[2];

	bool View;	// boolean check, ����� ���� (437 ~ 445)

	Item();
	// item_collide �Լ����� item�� ���ڷ� �޴´�. Ȯ�� �ʿ�.
	// item_zero, item_one �Լ����� item�� ���ڷ� �޴´�. Ȯ�� �ʿ�.
};
