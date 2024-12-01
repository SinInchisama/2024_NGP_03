#pragma once
#include <functional>
#include <queue>
#include "FunctionalPackets.h"

class EventQueue
{
public:
	void addEvent(const std::function<std::unique_ptr<Parent_Packet>()>& func) {
		queue.push(func);
	}

	void executeAll(std::queue<std::unique_ptr<Parent_Packet>>& p) {
		while (!queue.empty()) {
			auto event = queue.front();
			auto result = event();  // 이벤트를 실행하여 결과 얻기

			if (result) {
				p.push(std::move(result));  // nullptr이 아닌 경우에만 p에 추가
			}

			queue.pop();  // 큐에서 이벤트 제거
		}
	}

	static EventQueue* currentInstance;

private:
	std::queue<std::function<std::unique_ptr<Parent_Packet>()>> queue;
};