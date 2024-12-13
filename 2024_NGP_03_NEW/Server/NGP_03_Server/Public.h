#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Common.h"
#include <Windows.h>
#include "GameMaanger.h"
#include <random>

#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����

#define byte char
#define SERVERPORT 9000
#define BUFSIZE    1024

#define BOX_X 20
#define BOX_Y 20
#define BOX_Z 20

extern CRITICAL_SECTION cs;
extern byte index;

extern struct sockaddr_in clientaddr[2];

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

extern std::random_device rd;
extern std::mt19937 mt;
extern std::uniform_int_distribution<int> dist;


typedef enum : byte {
	KEY_UP = 0b0000'0001, // UP Ű			0000 0001		
	KEY_DOWN = 0b0000'0010, // DOWN Ű		0000 0010
	KEY_LEFT = 0b0000'0100, // LEFT Ű		0000 0100
	KEY_RIGHT = 0b0000'1000, // RIGHT Ű	0000 1000
	KEY_Q = 0b0001'0000, // Q Ű			0001 0000
	KEY_E = 0b0010'0000, // E Ű			0010 0000
	KEY_A = 0b0100'0000  // A Ű			0100 0000
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

#endif // COMMON_H