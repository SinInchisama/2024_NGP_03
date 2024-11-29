#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "CBullet.h"
#include "Public.h"

void EventMovePlayer(Player* p, KeyInput& k);
void EventCreateItem(Item* itemArr);
void EventCreateBullet(Bullet* bArr);
void EventMoveBullet(Bullet* bArr);
