#pragma once
#include "Common.h"
#include "fstream"
#include "iostream"
#include "Windows.h"
#include "Public.h"
#include "CPlayer.h"
#include <chrono>
#include "EventQueue.h"
#include "CBox.h"
#include "CTimer.h"
#include "CItem.h"
#include "FunctionalPackets.h"
#include "queue"

DWORD WINAPI WorkThread(LPVOID arg);
extern Box All_Box[20][20];


// ���� �������� �ð�
//std::chrono::high_resolution_clock::time_point previousTime;
//std::chrono::duration<float> deltaTime;

void Reset_Object();
void Send_Object();
void Timer_Check();

void Boxinit(int x, int y, int z);
void Item_Effect(int index, int num, int b);