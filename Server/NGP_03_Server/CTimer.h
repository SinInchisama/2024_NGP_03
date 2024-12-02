#pragma once
#include <time.h>

class Timer {
private:
	time_t startTime;
	time_t endTime;
	time_t previousTime;

	float deltaTime;
public:
	Timer(int seconds);	// 생성자

	void resetTimer();
	int getRemainingTiem();	// 남은 시간 반환
	bool isFinished();	// 시간 종료 여부
	time_t getStartTime() { return startTime; }
	time_t getPreviousTime() { return previousTime; }

	void setDeltaTime(float f) { deltaTime = f; }
	void setPreviousTime(time_t t) { previousTime = t; }

	std::unique_ptr<Parent_Packet> Update_timer(short index);
};