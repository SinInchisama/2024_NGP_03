#pragma once
#include "Common.h"
#include "fstream"
#include "iostream"
#include "Windows.h"
#include "Public.h"
#include "CPlayer.h"

DWORD WINAPI WorkThread(LPVOID arg);
extern Player players[2];
extern Box All_Box[20][20];

void Reset_Ojbect();

void Boxinit(int x, int y, int z);