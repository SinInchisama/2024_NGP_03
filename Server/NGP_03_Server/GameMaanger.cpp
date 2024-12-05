#include "GameMaanger.h"
#include "CPlayer.h"
#include "CBullet.h"

GameManger* GameManger::Instance = nullptr;

GameManger::GameManger()
{
	if (Instance == nullptr)
		Instance = this;
	Bullet bullet[2];

	players = new Player*[2];
	bullets = new Bullet * [2];
	for (int i = 0; i < 2; ++i)
	{
		players[i] = new Player{ i, {0.0f, 0.0f, 0.0f} };
		bullets[i] = new Bullet;
	}
}