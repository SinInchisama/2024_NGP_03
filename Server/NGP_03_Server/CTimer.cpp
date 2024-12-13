#include "CTimer.h"

Timer::Timer(int seconds) : gameDuration (seconds) {
	startTime = time(NULL);
	endTime = startTime + seconds; 
	// 여기랑 아래 resetTimer이랑 중복 아님? 5번 줄이랑 13번 줄 중 하나만 살리는 게 좋을 듯 - 안현우
	deltaTime = 0;
}

void Timer::resetTimer()
{
	startTime = time(NULL);
	endTime = startTime + gameDuration;
	// 생성자 호출 시에 인자로 넣어준 값을 멤버 변수에 저장해 resetTimer() 함수 호출 시에 다시 사용하도록 변경했음 - 안현우
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

std::unique_ptr<Parent_Packet> Timer::End_Game(byte b)
{
	return std::make_unique<End_game>(b);
}
