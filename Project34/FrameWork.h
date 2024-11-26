#pragma once
#pragma comment(lib, "lib/freeglut.lib")

#include "include/GL/glew.h"
#include "include/GL/glut.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Common.h"

#include <iostream>

extern float line[];            // line 배열 선언
extern float vPositionList[];   // vPositionList 배열 선언
extern unsigned int index[];    // index 배열 선언

class FrameWork
{
private:
	GLint result;

	GLuint triangleShaderProgramID;

	GLuint vao, vbo[2], EBO[2], linevbo[2], linevao;

	GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;
	GLuint triangleTextureCoordinateBufferObjectID;
	GLuint triangleVertexArrayObject;

	glm::mat4 view;
	glm::mat4 projection;

public:
	FrameWork();

	void Make_VertexShader();
	void Make_FragmentShader();

	void Init_Shader();
	
	void init_Buffer();
	void Define_VertexArrayObject();

	void Draw_Scene();

	GLvoid Reshape(int w, int h);

	static FrameWork* currentInstance;

	static void DisplayWrapper() {
		if (currentInstance) {
			currentInstance->Draw_Scene();
		}
	}

	static void DisplayReShape(int w,int h) {
		if (currentInstance) {
			currentInstance->Reshape(w,h);
		}
	}
};

