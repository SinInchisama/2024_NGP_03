#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

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

	void Change_Locate(int x, int z)	// 0 <= x, z < 20
	{
		float xScale = (float)10 / BOX_X;
		float zScale = (float)10 / BOX_Z;

		float xlocate = 5 - (xScale / 2);
		float zlocate = 5 - (zScale / 2);

		Ilocate[0] = xlocate - xScale * x;
		Ilocate[1] = 0.0f;
		Ilocate[2] = zlocate - zScale * z;
	}
};

void InitItem(Item& item)
{
	srand(time(NULL));
	glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };

	int x = rand() % 20;
	int z = rand() % 20;
	item.Change_Locate(x, z);
	item.Iscale = glm::vec3{ 0.3f,0.3f,0.3f };
	item.Item_type = rand() % 2;

	if (item.Item_type == 0)
		item.Icolor = glm::vec3{ 1.0f,0.0f,1.0f };
	else if (item.Item_type == 1)
		item.Icolor = glm::vec3{ 1.0f,1.0f,1.0f };

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	Scale = glm::scale(Scale, glm::vec3(item.Iscale)); //		각 사각형 크기 
	Tx = glm::translate(Tx, item.Ilocate);

	item.TR = Tx * Scale * TR;

	item.Bounding_box[0] = {(item.Ilocate - bound_scale), 1.f};
	item.Bounding_box[1] = { (item.Ilocate + bound_scale), 1.f };
	 
	item.View = false;
}