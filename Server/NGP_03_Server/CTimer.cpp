#include "CTimer.h"

Timer::Timer(int seconds) {
	startTime = time(NULL);
	endTime = startTime + seconds; 
	deltaTime = 0;
}

void Timer::resetTimer()
{
	startTime = time(NULL);
	endTime = startTime + 10;
	previousTime = time(NULL);
}

int Timer::getRemainingTiem() {
	time_t currentTime = time(NULL);
	int remainingTime = (int)(endTime - currentTime);
	return remainingTime > 0 ? remainingTime : 0;	// 음수 방지
}

bool Timer::isFinished() {
	return previousTime >= endTime;
}

std::unique_ptr<Parent_Packet> Timer::End_Game()
{
	return std::make_unique<End_game>();
}
