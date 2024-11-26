#pragma once
#pragma comment(lib, "lib/freeglut.lib")

#include "Common.h"
#include "CPlayer.h"
#include "include/GL/glut.h"

class State
{
public:
	virtual void Update() {};
	virtual void Draw() {};

	virtual void SKeyUp(int key) {};
	virtual void SKeyDown(int key) {};

	virtual void KeyUp(int key) {  };
	virtual void KeyDown(int key) {};
};

class Play_State :State
{
private:
	Player player = { 0, {0.0f, 0.0f, 0.0f} };

	Box All_Box[20][20];
public:
	Play_State();

	void Update() override;
	void Draw()override;

	void SKeyUp(int key) override;
	void SKeyDown(int key)override;;

	void KeyUp(int key);
	void KeyDown(int key);

	void Boxinit(int x, int y, int z);
};