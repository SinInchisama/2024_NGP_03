#include "CTimer.h"

Timer::Timer(int seconds) {
	startTime = time(NULL);
	endTime = startTime + seconds;
}

int Timer::getRemainingTiem() {
	time_t currentTime = time(NULL);
	int remainingTime = (int)(endTime - currentTime);
	return remainingTime > 0 ? remainingTime : 0;	// ���� ����
}

bool Timer::isFinished() {
	return time(NULL) >= endTime;
}