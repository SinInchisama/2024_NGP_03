#pragma once
#include "include/glm/glm.hpp"

class Item {
public:
	int Item_type;	// 비교 연산

	glm::vec3 Iscale;
	glm::vec3 Ilocate;
	glm::vec3 Icolor;
	glm::mat4 TR;

	glm::vec4 Bounding_box[2];

	bool View;	// boolean check, 덮어쓰기 연산 (437 ~ 445)

	// item_collide 함수에서 item을 인자로 받는다. 확인 필요.
	// item_zero, item_one 함수에서 item을 인자로 받는다. 확인 필요.
};
