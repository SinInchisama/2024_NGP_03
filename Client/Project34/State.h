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
	Player player = { 0, {0.0f, 0.0f, 0.0f} };

	Box All_Box[20][20];

	Bullet bullet[2];

	Item item[20];
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

};

class Stay_State :public State
{
private:
	Texture Logo_texture;
public:
	Stay_State();

	void enter()override {};
	void exit()override {};

	void Update() override {};
	void Draw()override;

	void SKeyUp(int key) override {};
	void SKeyDown(int key)override {};

	void KeyUp(int key) {};
	void KeyDown(int key) ;
};