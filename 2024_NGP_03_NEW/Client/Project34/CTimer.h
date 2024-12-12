#pragma once
#include <time.h>

class Timer {
private:
	time_t startTime;
	time_t endTime;

public:
	Timer(int seconds);	// 생성자
	int getRemainingTiem();	// 남은 시간 반환
	bool isFinished();	// 시간 종료 여부
};