#pragma once
class State
{
public:
	virtual void Draw();
	virtual void KeyUp();
	virtual void KeyDown();
};

class Play_State :State
{
public:
	Play_State() {};

	void Draw()override;
	void KeyUp()override;
	void KeyDown()override;
};