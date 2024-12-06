#pragma once
#pragma comment(lib, "lib/freeglut.lib")

#include "Public.h"
#include "CPlayer.h"
#include "CBox.h"
#include "CBullet.h"
#include "CItem.h"
#include "include/GL/glut.h"
#include "Texture.h"
#include "FrameWork.h"
#include "FunctionalPackets.h"

class State
{
public:
	virtual void enter() {};
	virtual void exit() {};

	virtual void Update() {};
	virtual void Draw() {};

	virtual void SKeyUp(int key) {};
	virtual void SKeyDown(int key) {};

	virtual void KeyUp(int key) {};
	virtual void KeyDown(int key) {};
};

class Play_State :public State
{
public:
	Player player[2] = { {0, {0.0f, 0.0f, 0.0f}},{0, {0.0f, 0.0f, 0.0f}} };

	Box All_Box[20][20];

	Bullet bullet[2];

	Item item[20];

	Texture Time_Count[2];

	Texture Score[3];

	GLuint Num[11];
	
	short Time = 0;

	char My_index;

	glm::vec3 Camerapos{ 0.0,8.0,15.0 };
	glm::vec3 Cameradirection{0.0,0.0,-1.0};
	glm::vec3 Cameraup{0.0,1.0,0.0};
public:
	Play_State();

	void enter()override ;
	void exit()override {};

	void Update() override;
	void Draw()override;

	void SKeyUp(int key) override;
	void SKeyDown(int key)override;;

	void KeyUp(int key);
	void KeyDown(int key);

	void Draw_Score(Player& player);
};

class Stay_State :public State
{
private:
	Texture Logo_texture;
public:
	Stay_State();

	void enter()override {};
	void exit()override {};

	void Update() override ;
	void Draw()override;

	void SKeyUp(int key) override {};
	void SKeyDown(int key)override {};

	void KeyUp(int key) {};
	void KeyDown(int key) ;
};

class End_State :public State
{
private:
	Texture Win_texture[2];
public:
	End_State();

	void enter()override {};
	void exit()override {};

	void Update() override {};
	void Draw()override;

	void SKeyUp(int key) override {};
	void SKeyDown(int key)override {};

	void KeyUp(int key) {};
	void KeyDown(int key) {};
};