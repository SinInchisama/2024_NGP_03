#pragma once

class Player;
class Bullet;

class GameManger
{
public:
	Player** players;
	Bullet** bullets;

public:
	GameManger();

	static GameManger* Instance;
};