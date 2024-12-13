#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Common.h"

#define byte char

extern GLuint s_program;

extern GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
extern GLuint vertexshader, fragmentshader; //--- 세이더 객체

extern GLuint Text_vertexShader;
extern GLuint Text_fragmentShader;

extern GLuint triangleShaderProgramID;

extern GLuint vao, vbo[2], EBO[2], linevbo[2], linevao;

extern GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;
extern GLuint triangleTextureCoordinateBufferObjectID;
extern GLuint triangleVertexArrayObject;

extern glm::vec3 cameraUp; //--- 카메라 위쪽 방향

extern SOCKET sock;

extern byte Win;

typedef enum : byte {
	KEY_UP =	0b0000'0001, // UP 키		0000 0001		
	KEY_DOWN =	0b0000'0010, // DOWN 키		0000 0010
	KEY_LEFT =	0b0000'0100, // LEFT 키		0000 0100
	KEY_RIGHT = 0b0000'1000, // RIGHT 키	0000 1000
	KEY_Q =		0b0001'0000, // Q 키		0001 0000
	KEY_E =		0b0010'0000, // E 키		0010 0000
	KEY_A =		0b0100'0000  // A 키		0100 0000
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
	PACKET_UPDATE_SCORE = 0x09, // Update_score
	PACKET_END_GAME = 0x10
} PacketType;

typedef struct playerInput {
	byte p_index; // - 플레이어 1인지 2인지 구분(1 or 2)
	byte input_key; // - 1 ~ 7 입력된 키 정보
} playerInput;


char* filetobuf(const char* file);

//typedef struct Box {
//	glm::vec3 Bscale;
//	glm::vec3 Blocate;
//	glm::vec3 Bcolor;
//	glm::mat4 TR;
//
//	int offset;
//
//	glm::vec4 Bounding_box[2];
//}Box;

typedef struct Update_score {
	short my_score;
	short enermy_score;
};
#endif // COMMON_H