#pragma once
#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Common.h"

class FrameWork
{
private:
	GLuint s_program;

	GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
	GLuint vertexshader, fragmentshader; //--- 세이더 객체

	GLuint Text_vertexShader;
	GLuint Text_fragmentShader;

	GLint result;

	GLuint triangleShaderProgramID;

	GLuint vao, vbo[2], EBO[2], linevbo[2], linevao;

	GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;
	GLuint triangleTextureCoordinateBufferObjectID;
	GLuint triangleVertexArrayObject;

public:
	FrameWork();

	void Make_VertexShader();
	void Make_FragmentShader();

	void Init_Shader();
	
	void init_Buffer();
	void Define_VertexArrayObject();

	void Draw_Scene();

	GLvoid Reshape(int w, int h);
};

