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

char* filetobuf(const char* file);
#endif // COMMON_H