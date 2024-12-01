#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "CBullet.h"
#include "Public.h"
#include <vector>
#include "CBox.h"

void EventMovePlayer(Player* p, KeyInput& k);
//void EventCreateItem(Item* itemArr);
//void EventCreateBullet(Bullet* bArr);
//void EventMoveBullet(Bullet* bArr);

void process_received_data(const char* buffer, size_t buffer_size,Player* p,Box All_Box[20][20]);

struct Parent_Packet {
	byte pakcet_type;

    virtual void serialize(char* buffer)const{}

    virtual ~Parent_Packet() = default;
};

struct Move_Packet : Parent_Packet {
	byte player_index;
	glm::vec3 move;

    Move_Packet() : player_index(0), move(0.0f, 0.0f, 0.0f) {
        pakcet_type = 1; // Move_Packet�� Ÿ�� ����
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

struct Change_floor : Parent_Packet {
    short box_index;
    glm::vec3 color;

    Change_floor() : box_index(0), color(0.0f, 0.0f, 0.0f) {
        pakcet_type = 2; // Move_Packet�� Ÿ�� ����
    }

    Change_floor(char b_idx, const glm::vec3& b_color)
        : box_index(b_idx), color(b_color) {
        pakcet_type = 2; // Move_Packet Ÿ�� ����
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &box_index, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &color, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }

    void deserializePlayer(const char* buffer)
    {
        int offset = 0;
        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&box_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&color, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }
};