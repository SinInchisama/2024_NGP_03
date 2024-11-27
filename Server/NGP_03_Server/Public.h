#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Common.h"
#include "Windows.h"

#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����

#define byte char
#define SERVERPORT 9000
#define BUFSIZE    1024

extern CRITICAL_SECTION cs;
extern byte index;

extern GLuint s_program;

extern GLchar* vertexsource, * fragmentsource; //--- �ҽ��ڵ� ���� ����
extern GLuint vertexshader, fragmentshader; //--- ���̴� ��ü

extern GLuint Text_vertexShader;
extern GLuint Text_fragmentShader;

extern GLuint triangleShaderProgramID;

extern GLuint vao, vbo[2], EBO[2], linevbo[2], linevao;

extern GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;
extern GLuint triangleTextureCoordinateBufferObjectID;
extern GLuint triangleVertexArrayObject;

extern glm::vec3 cameraUp; //--- ī�޶� ���� ����

extern SOCKET client_sock[2];

typedef enum : byte {
	KEY_UP = 0x01, // UP Ű
	KEY_DOWN = 0x02, // DOWN Ű
	KEY_LEFT = 0x04, // LEFT Ű
	KEY_RIGHT = 0x08, // RIGHT Ű
	KEY_Q = 0x10, // Q Ű (0x016 -> 0x10)
	KEY_E = 0x20, // E Ű (0x032 -> 0x20)
	KEY_A = 0x40 // A Ű (0x064 -> 0x40)
} KeyInput;

typedef enum {
	PACKET_MOVE_PLAYER = 0x01, // Move_Player
	PACKET_CREATE_BULLET = 0x02, // Create_bullet
	PACKET_CREATE_ITEM = 0x03, // Create_Item
	PACKET_DELETE_ITEM = 0x04, // Delete_Item
	PACKET_DELETE_BULLET = 0x05, // Delete_bullet
	PACKET_CHANGE_FLOOR = 0x06, // Change_floor
	PACKET_MOVE_BULLET = 0x07, // Move_bullet
	PACKET_UPDATE_TIMER = 0x08, // Update_timer
	PACKET_UPDATE_SCORE = 0x09 // Update_score
} PacketType;

typedef struct playerInput {
	byte p_index; // - �÷��̾� 1���� 2���� ����(1 or 2)
	byte input_key; // - 1 ~ 7 �Էµ� Ű ����
} playerInput;


char* filetobuf(const char* file);

typedef struct Box {
	glm::vec3 Bscale;
	glm::vec3 Blocate;
	glm::vec3 Bcolor;
	glm::mat4 TR;

	int offset;

	glm::vec4 Bounding_box[2];
}Box;
#endif // COMMON_H