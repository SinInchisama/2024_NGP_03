#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"
#include "FunctionalPackets.h"

class Box {
public:
	//glm::vec3 Bcolor;
	glm::mat4 TR;

	glm::vec3 Color = { 0.0f, 0.0f, 0.0f }; // ���� �⺻ ����

	glm::vec4 Bounding_box[2];

	//glm::vec3 Get_Color() { return Bcolor; }

	GLfloat Get_R() { return Color[0]; }
	GLfloat Get_G() { return Color[1]; }
	GLfloat Get_B() { return Color[2]; }

	void serializeBox(char* buffer) const;
	void deserializeBox(const char* buffer);

	// �÷��̾�� �浹�� �ش� �÷��̾��� ���� ������
	std::unique_ptr<Parent_Packet> Chage_Color(glm::vec3 v,short index);

	// �� �κ��� �浹üũ �κп��� �ذ��ؾ��ϴ°�?
	//bool Crash_Player()
};