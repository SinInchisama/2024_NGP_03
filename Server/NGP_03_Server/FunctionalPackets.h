#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "CBullet.h"
#include "Public.h"
#include <vector>

void EventMovePlayer(Player* p, KeyInput& k);
void EventCreateItem(Item* itemArr);
void EventCreateBullet(Bullet* bArr);
void EventMoveBullet(Bullet* bArr);

struct Parent_Packet {
	byte pakcet_type;

	virtual std::vector<char> serialize() const {                   // 데이터를 보내기 위한 직렬화
		std::vector<char> buffer(sizeof(Parent_Packet));
		std::memcpy(buffer.data(), this, sizeof(Parent_Packet));
		return buffer;
	}

    virtual ~Parent_Packet() = default;
};

struct Move_Packet : Parent_Packet {
	byte player_index;
	glm::vec3 move;

    Move_Packet() { pakcet_type = 1; } // Move_Packet의 기본 packet_type

    std::vector<char> serialize() const override {          // 데이터를 보내기 위한 직렬화
        std::vector<char> buffer(sizeof(Move_Packet));
        std::memcpy(buffer.data(), this, sizeof(Move_Packet));
        return buffer;
    }

    static Move_Packet deserialize(const char* data) {      // 데이터를 보내기 위한 역직렬화
        Move_Packet packet;
        std::memcpy(&packet, data, sizeof(Move_Packet));
        return packet;
    }
};

