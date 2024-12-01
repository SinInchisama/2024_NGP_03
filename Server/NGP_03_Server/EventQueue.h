#pragma once
#include <functional>
#include <queue>

class EventQueue
{
public:
	void addEvent(const std::function<std::unique_ptr<Parent_Packet>()>& func) {
		queue.push(func);
	}

	void executeAll(std::queue<std::unique_ptr<Parent_Packet>>& p) {
		while (!queue.empty()) {
			auto event = queue.front();
			p.push(event());
			queue.pop();
		}
	}

	static EventQueue* currentInstance;

private:
	std::queue<std::function<std::unique_ptr<Parent_Packet>()>> queue;
};