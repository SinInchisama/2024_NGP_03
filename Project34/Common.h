#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

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