#include "CTimer.h"

Timer::Timer(int seconds) : gameDuration (seconds) {
	startTime = time(NULL);
	endTime = startTime + seconds; 
	// ����� �Ʒ� resetTimer�̶� �ߺ� �ƴ�? 5�� ���̶� 13�� �� �� �ϳ��� �츮�� �� ���� �� - ������
	deltaTime = 0;
}

void Timer::resetTimer()
{
	startTime = time(NULL);
	endTime = startTime + gameDuration;
	// ������ ȣ�� �ÿ� ���ڷ� �־��� ���� ��� ������ ������ resetTimer() �Լ� ȣ�� �ÿ� �ٽ� ����ϵ��� �������� - ������
	previousTime = time(NULL);
}

int Timer::getRemainingTiem() {
	time_t currentTime = time(NULL);
	int remainingTime = (int)(endTime - currentTime);
	return remainingTime > 0 ? remainingTime : 0;	// ���� ����
}

bool Timer::isFinished() {
	return previousTime >= endTime;
}

std::unique_ptr<Parent_Packet> Timer::End_Game(byte b)
{
	return std::make_unique<End_game>(b);
}
