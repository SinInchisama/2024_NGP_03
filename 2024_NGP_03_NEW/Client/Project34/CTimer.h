#pragma once
#include <time.h>

class Timer {
private:
	time_t startTime;
	time_t endTime;

public:
	Timer(int seconds);	// ������
	int getRemainingTiem();	// ���� �ð� ��ȯ
	bool isFinished();	// �ð� ���� ����
};