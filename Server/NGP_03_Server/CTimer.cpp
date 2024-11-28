#include "CTimer.h"

Timer::Timer(int seconds) {
	startTime = time(NULL);
	endTime = startTime + seconds; 
	deltaTime = 0;
}

void Timer::resetTimer()
{
	startTime = time(NULL);
	endTime = startTime + 60;
	previousTime = time(NULL);
}

int Timer::getRemainingTiem() {
	time_t currentTime = time(NULL);
	int remainingTime = (int)(endTime - currentTime);
	return remainingTime > 0 ? remainingTime : 0;	// 음수 방지
}

bool Timer::isFinished() {
	return time(NULL) >= endTime;
}