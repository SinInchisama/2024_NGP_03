#pragma once
#include <functional>
#include <queue>

class EventQueue
{
public:
	void addEvent(const std::function<void()>& func) {
		queue.push(func);
	}

	void executeAll() {
		while (!queue.empty()) {
			auto event = queue.front();
			event();
			queue.pop();
		}
	}

	static EventQueue* currentInstance;

private:
	std::queue<std::function<void()>> queue;
};