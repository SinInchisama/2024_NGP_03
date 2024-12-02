#include "GameMaanger.h"
#include "CPlayer.h"

GameManger* GameManger::Instance = nullptr;

GameManger::GameManger()
{
	if (Instance == nullptr)
		Instance = this;

	Player player[2] = { {0, {0.0f, 0.0f, 0.0f}},{0, {0.0f, 0.0f, 0.0f}} };

	players = new Player*[2];
	for (int i = 0; i < 2; ++i)
	{
		players[i] = new Player{ 0, {0.0f, 0.0f, 0.0f} };
	}
}