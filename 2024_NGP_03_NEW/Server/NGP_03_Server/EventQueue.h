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
			auto result = event();  // �̺�Ʈ�� �����Ͽ� ��� ���

			if (result) {
				p.push(std::move(result));  // nullptr�� �ƴ� ��쿡�� p�� �߰�
			}

			queue.pop();  // ť���� �̺�Ʈ ����
		}
	}

	static EventQueue* currentInstance;

private:
	std::queue<std::function<std::unique_ptr<Parent_Packet>()>> queue;
};