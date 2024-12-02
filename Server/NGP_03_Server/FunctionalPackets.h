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

struct Parent_Packet {
    byte pakcet_type;

    virtual void serialize(char* buffer)const {}

    virtual ~Parent_Packet() = default;
};

struct Move_Packet : Parent_Packet {
    byte player_index;
    glm::vec3 move;

    Move_Packet() : player_index(0), move(0.0f, 0.0f, 0.0f) {
        pakcet_type = 1; // Move_Packet의 타입 설정
    }

    Move_Packet(char player_idx, const glm::vec3& player_move)
        : player_index(player_idx), move(player_move) {
        pakcet_type = 1; // Move_Packet 타입 설정
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        std::cout << move.x<<" " << move.y << " " << move.z << std::endl;
        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &player_index, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &move, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }

    void deserializePlayer(const char* buffer)
    {
        int offset = 0;
        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&player_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&move, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }
};

struct Change_floor : Parent_Packet {
    short box_index;
    glm::vec3 color;

    Change_floor() : box_index(0), color(0.0f, 0.0f, 0.0f) {
        pakcet_type = 2; // Move_Packet의 타입 설정
    }

    Change_floor(char b_idx, const glm::vec3& b_color)
        : box_index(b_idx), color(b_color) {
        pakcet_type = 2; // Move_Packet 타입 설정
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

struct Update_timer : Parent_Packet {
    short timer;

    Update_timer() : timer(0) {
        pakcet_type = 3;
    }

    Update_timer(const short G_timer)
        : timer(G_timer) {
        pakcet_type = 3;
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &timer, sizeof(short)); offset += sizeof(short);
    }

    void deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&timer, buffer + offset, sizeof(short)); offset += sizeof(short);
    }
};

struct Create_item : Parent_Packet {
    short item_index;
    glm::vec3 color;
    glm::vec3 locate;

    Create_item() : item_index(0), color(0.0f, 0.0f, 0.0f), locate(0.0f, 0.0f, 0.0f) {
        pakcet_type = 4;
    }

    Create_item(char i_idx, const glm::vec3& i_color, const glm::vec3& i_locate)
        : color(i_color), locate(i_locate) {
        pakcet_type = 4;
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &item_index, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &color, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
        memcpy(buffer + offset, &locate, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }

    void deserializePlayer(const char* buffer)
    {
        int offset = 0;
        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&item_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&color, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
        memcpy(&locate, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }
};

struct Delete_item : Parent_Packet {
    short item_index;

    Delete_item() : item_index(0) {
        pakcet_type = 5;
    }

    Delete_item(const short i_idx)
        : item_index(item_index) {
        pakcet_type = 5;
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &item_index, sizeof(short)); offset += sizeof(short);
    }

    void deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&item_index, buffer + offset, sizeof(short)); offset += sizeof(short);
    }
};