#pragma once
#include "Common.h"
#include "CPlayer.h"

class State
{
public:
	virtual void Draw() {};
	virtual void KeyUp() {};
	virtual void KeyDown() {};
	virtual void Update() {};
};

class Play_State :State
{
private:
	Player player = { 0, {0.0f, 0.0f, 0.0f} };

	Box All_Box[20][20];
public:
	Play_State();

	void Draw()override;
	void KeyUp() override {};
	void KeyDown()override {};

	void Boxinit(int x, int y, int z);
};