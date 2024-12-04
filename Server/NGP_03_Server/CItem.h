#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"
#include "FunctionalPackets.h"


class Item {
public:
	int Item_type;	// 비교 연산, 최초 전달 정보

	glm::vec3 IScale;
	glm::vec3 ILocate;	//최초 전달 정보
	glm::vec3 IColor;	// 최초 전달 정보
	glm::mat4 TR;		// 최초 전달 정보

	glm::vec4 Bounding_box[2];	// 최초 전달 정보

	bool View;	// boolean check, 덮어쓰기 연산 (437 ~ 445)

	GLfloat Get_R() { return IColor[0]; }
	GLfloat Get_G() { return IColor[1]; }
	GLfloat Get_B() { return IColor[2]; }

	// item_collide 함수에서 item을 인자로 받는다. 확인 필요.
	// item_zero, item_one 함수에서 item을 인자로 받는다. 확인 필요.

	// Create Item을 위한
	Item() {};

	void serializeItem(char* buffer) const;
	void deserializeItem(const char* buffer);

	void Item_reset(int type, const glm::vec3& location);

	static std::unique_ptr<Parent_Packet> Create_Item(Item* item)
	{
		int index = 0;
		for (; index < 20; ++index) {
			if (!item[index].View) {
				int randomType = 1;
				glm::vec3 randomLocation(static_cast<float>(rand() % 8 - 4), 0.0f, static_cast<float>(rand() % 8 - 4));
				item[index].Item_reset(randomType, randomLocation);
				item[index].View = true;

				return std::make_unique<Create_item>(index, item[index].IColor, item[index].ILocate);
			}
		}

		return nullptr;
	};

	static std::unique_ptr<Parent_Packet> Delete_Item(Item* item, int i)
	{
		// 인덱스 유효성 검사
		if (i < 0 || i >= 20) {
			return nullptr;	// 잘못된 인덱스는 무시
		}

		// 아이템 비활성화
		item[i].View = false;

		// Delete_item 패킷 생성 및 반환
		return std::make_unique<Delete_item>(static_cast<short>(i));
	}
};

//void InitItem(Item& item)
//{
//	srand(time(NULL));
//	glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };
//
//	int x = rand() % 20;
//	int z = rand() % 20;
//	item.Change_Locate(x, z);
//	item.Iscale = glm::vec3{ 0.3f,0.3f,0.3f };
//	item.Item_type = rand() % 2;
//
//	if (item.Item_type == 0)
//		item.Icolor = glm::vec3{ 1.0f,0.0f,1.0f };
//	else if (item.Item_type == 1)
//		item.Icolor = glm::vec3{ 1.0f,1.0f,1.0f };
//
//	glm::mat4 TR = glm::mat4(1.0f);
//	glm::mat4 Tx = glm::mat4(1.0f);
//	glm::mat4 Scale = glm::mat4(1.0f);
//
//	Scale = glm::scale(Scale, glm::vec3(item.Iscale)); //		각 사각형 크기 
//	Tx = glm::translate(Tx, item.Ilocate);
//
//	item.TR = Tx * Scale * TR;
//
//	item.Bounding_box[0] = {(item.Ilocate - bound_scale), 1.f};
//	item.Bounding_box[1] = { (item.Ilocate + bound_scale), 1.f };
//	 
//	item.View = false;
//}
//
//void Item::serializeItem(char* buffer) const
//{
//	// Serialize int Item_type 
//	memcpy(buffer, &Item_type, sizeof(Item_type));
//	buffer += sizeof(Item_type);
//
//	// Serialize glm::vec3 Locate (3 floats)
//	memcpy(buffer, &Ilocate, sizeof(Ilocate));
//	buffer += sizeof(Ilocate);
//
//	// Serialize glm::vec3 Color (3 floats)
//	memcpy(buffer, &Icolor, sizeof(Icolor));
//	buffer += sizeof(Icolor);
//
//	// Serialize glm::mat4 TR (16 floats)
//	memcpy(buffer, &TR, sizeof(TR));
//	buffer += sizeof(TR);
//
//	// Serialize glm::vec4 Bounding_box (2 vec4s)
//	memcpy(buffer, &Bounding_box, sizeof(Bounding_box));
//}
//
//void Item::deserializeItem(const char* buffer)
//{
//	// Deserialize int Item_type 
//	memcpy(&Item_type, buffer, sizeof(Item_type));
//	buffer += sizeof(Item_type);
//
//	// Deserialize glm::vec3 Locate (3 floats)
//	memcpy(&Ilocate, buffer, sizeof(Ilocate));
//	buffer += sizeof(Ilocate);
//
//	// Deserialize glm::vec3 Color (3 floats)
//	memcpy(&Icolor, buffer, sizeof(Icolor));
//	buffer += sizeof(Icolor);
//
//	// Deserialize glm::mat4 TR (16 floats)
//	memcpy(&TR, buffer, sizeof(TR));
//	buffer += sizeof(TR);
//
//	// Deserialize glm::vec4 Bounding_box (2 vec4s)
//	memcpy(&Bounding_box, buffer, sizeof(Bounding_box));
//}
