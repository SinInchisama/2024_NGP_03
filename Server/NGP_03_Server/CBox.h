#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"
#include "FunctionalPackets.h"

class Box {
public:
	//glm::vec3 Bcolor;
	glm::mat4 TR;

	glm::vec3 Color = { 0.0f, 0.0f, 0.0f }; // 상자 기본 색깔

	glm::vec4 Bounding_box[2];

	//glm::vec3 Get_Color() { return Bcolor; }

	GLfloat Get_R() { return Color[0]; }
	GLfloat Get_G() { return Color[1]; }
	GLfloat Get_B() { return Color[2]; }

	void serializeBox(char* buffer) const;
	void deserializeBox(const char* buffer);

	// 플레이어와 충돌시 해당 플레이어의 색깔 얻어오기
	std::unique_ptr<Parent_Packet> Chage_Color(glm::vec3 v,short index);

	// 이 부분은 충돌체크 부분에서 해결해야하는가?
	//bool Crash_Player()
};