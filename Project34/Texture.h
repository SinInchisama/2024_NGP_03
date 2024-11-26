#pragma once

#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/GL/glew.h"
#include "include/FreeImage.h"

#include <iostream>

using namespace std;

typedef struct Texture {
	glm::vec3 Tlocate;
	int Trotate;
	glm::vec3 Tscale;
	glm::mat4 Ttr;

	GLuint text;
}Texture;

GLuint CreateTexture(char const* filename);
