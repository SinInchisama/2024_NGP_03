#pragma once

class Player;

class GameManger
{
public:
	Player** players;

public:
	GameManger();

	static GameManger* Instance;
};