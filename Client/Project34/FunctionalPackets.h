#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "CBullet.h"
#include "Public.h"
#include <vector>

void EventMovePlayer(Player* p, KeyInput& k);
//void EventCreateItem(Item* itemArr);
//void EventCreateBullet(Bullet* bArr);
//void EventMoveBullet(Bullet* bArr);

void process_received_data(const char* buffer, size_t buffer_size);

struct Parent_Packet {
	byte pakcet_type;

    virtual void serialize(char* buffer)const{}

    virtual ~Parent_Packet() = default;
};

struct Move_Packet : Parent_Packet {
	byte player_index;
	glm::vec3 move;

    Move_Packet() : player_index(0), move(0.0f, 0.0f, 0.0f) {
        pakcet_type = 1; // Move_Packet의 타입 설정
    }

     void serialize(char* buffer)const override{
         int offset = 0;

         memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
         memcpy(buffer + offset, &player_index, sizeof(byte)); offset += sizeof(byte);
         memcpy(buffer + offset, &move, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
     }

     void deserializePlayer(const char* buffer)
     {
         int offset = 0;
         memcpy(&pakcet_type,buffer + offset, sizeof(byte)); offset += sizeof(byte);
         memcpy(&player_index,buffer + offset, sizeof(byte)); offset += sizeof(byte);
         memcpy(&move,buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }
};

