#pragma once
#include <time.h>
#include "FunctionalPackets.h"

class Timer {
private:
	time_t startTime;
	time_t endTime;
	time_t previousTime;
	time_t lastItemTime; // 마지막 아이템 생성 시간

	float deltaTime;
public:
	Timer(int seconds);	// 생성자

	void resetTimer();
	int getRemainingTiem();	// 남은 시간 반환
	bool isFinished();	// 시간 종료 여부
	time_t getStartTime() { return startTime; }
	time_t getPreviousTime() { return previousTime; }

	void setLastItemTime(time_t time) { lastItemTime = time; }
	time_t getLastItemTime() const { return lastItemTime; }

	void setDeltaTime(float f) { deltaTime = f; }
	void setPreviousTime(time_t t) { previousTime = t; }

	static std::unique_ptr<Parent_Packet> Update_Timer(short time) {
		return std::make_unique<Update_timer>(time);
	};
	//std::unique_ptr<Parent_Packet> Update_timer(short index);
};