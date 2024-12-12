#pragma once
#pragma comment(lib, "lib/freeglut.lib")

#include "include/GL/glew.h"
#include "include/GL/glut.h"
#include "include/glm/glm.hpp"
#include "include/glm/ext.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "Public.h"
#include "Common.h"

#include <iostream>
#include <vector>

extern float line[];            // line 배열 선언
extern float vPositionList[];   // vPositionList 배열 선언
extern unsigned int index[];    // index 배열 선언

class State;

class FrameWork
{
private:
	GLint result;

	glm::mat4 view;
	glm::mat4 projection;

	std::vector<State*> states;  // 상태들을 저장할 벡터
	int currentStateIndex;       // 현재 상태 인덱스
public:
	FrameWork();
	//~FrameWork() ;

	void Make_VertexShader();
	void Make_FragmentShader();

	void Init_Shader();
	
	void init_Buffer();
	void Define_VertexArrayObject();

	void Update(int value);

	void Draw_Scene();

	GLvoid Reshape(int w, int h);

	void KeyDownboard(int key, int x, int y);
	void KeyUpboard(int key, int x, int y);

	void SKeyDownboard(int key, int x, int y);
	void SKeyUpboard(int key, int x, int y);

	void Enter_State();
	void Exit_State();

	static FrameWork* currentInstance;

	static void DisplayWrapper() {
			currentInstance->Draw_Scene();
	}

	static void DisplayReShape(int w,int h) {
		currentInstance->Reshape(w,h);
	}

	/*static void Update() {
		currentInstance->Update();
	}*/
};

