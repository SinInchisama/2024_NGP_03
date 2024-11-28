#pragma once
#include "Common.h"
#include "fstream"
#include "iostream"
#include "Windows.h"
#include "Public.h"
#include "CPlayer.h"
#include "time.h"

DWORD WINAPI WorkThread(LPVOID arg);
extern Player players[2];
extern Box All_Box[20][20];

void Reset_Object();
void Send_Object();
void Timer_Check();

void Boxinit(int x, int y, int z);