#include "Public.h"

CRITICAL_SECTION cs;
byte index = 0;
SOCKET client_sock[2];
struct sockaddr_in clientaddr[2];

GLuint s_program = 0;
GLchar* vertexsource = nullptr;
GLchar* fragmentsource = nullptr;
GLuint vertexshader = 0;
GLuint fragmentshader = 0;

GLuint Text_vertexShader = 0;
GLuint Text_fragmentShader = 0;

GLuint triangleShaderProgramID = 0;

GLuint vao = 0;
GLuint vbo[2] = { 0 };
GLuint EBO[2] = { 0 };
GLuint linevbo[2] = { 0 };
GLuint linevao = 0;

GLuint trianglePositionVertexBufferObjectID = 0;
GLuint triangleColorVertexBufferObjectID = 0;
GLuint triangleTextureCoordinateBufferObjectID = 0;
GLuint triangleVertexArrayObject = 0;

glm::vec3 cameraUp; //--- 카메라 위쪽 방향\

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(0, 400);

bool gameEnd = true;

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fopen_s(&fptr,file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}