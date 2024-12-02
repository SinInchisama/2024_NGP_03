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

void process_received_data(const char* buffer, size_t buffer_size,Player* p,Box All_Box[20][20],Bullet* bullet);

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

struct Create_bullet : public Parent_Packet {
    byte player_index; // �÷��̾� �ε���
    bool b;        // �Ѿ� �ε���

    // �⺻ ������
    Create_bullet() : player_index(0), b(true) {
        pakcet_type = 3; // Create_bullet�� ��Ŷ Ÿ�� ����
    }

    // ����� ���� ������
    Create_bullet(byte p_idx, bool a) : player_index(p_idx), b(a) {
        pakcet_type = 3; // Create_bullet�� ��Ŷ Ÿ�� ����
    }

    // ����ȭ �޼���
    void serialize(char* buffer) const override {
        int offset = 0;


        // Parent_Packet�� pakcet_type ����ȭ
        memcpy(buffer + offset, &pakcet_type, sizeof(byte));
        offset += sizeof(byte);

        // player_index ����ȭ
        memcpy(buffer + offset, &player_index, sizeof(byte));
        offset += sizeof(byte);

        // index ����ȭ
        memcpy(buffer + offset, &b, sizeof(bool));
        offset += sizeof(b);
    }

    // ������ȭ �޼���
    void deserializePlayer(const char* buffer) {
        int offset = 0;

        // Parent_Packet�� pakcet_type ������ȭ
        memcpy(&pakcet_type, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // player_index ������ȭ
        memcpy(&player_index, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // index ������ȭ
        memcpy(&b, buffer + offset, sizeof(bool));
        offset += sizeof(b);
    }
};

struct Move_bullet : public Parent_Packet {
    byte player_index;  // �÷��̾� �ε���
    glm::vec3 position; // �Ѿ� ��ġ ����

    // �⺻ ������
    Move_bullet() : player_index(0), position(0.0f, 0.0f, 0.0f) {
        pakcet_type = 7; // Move_bullet ��Ŷ Ÿ�� ����
    }

    // ����� ���� ������
    Move_bullet(byte p_idx, const glm::vec3& pos)
        : player_index(p_idx), position(pos) {
        pakcet_type = 4; // Move_bullet ��Ŷ Ÿ�� ����
    }

    // ����ȭ �޼���
    void serialize(char* buffer) const override {
        int offset = 0;

        // Parent_Packet�� pakcet_type ����ȭ
        memcpy(buffer + offset, &pakcet_type, sizeof(byte));
        offset += sizeof(byte);

        // player_index ����ȭ
        memcpy(buffer + offset, &player_index, sizeof(byte));
        offset += sizeof(byte);

        // position (glm::vec3) ����ȭ
        memcpy(buffer + offset, &position, sizeof(glm::vec3));
        offset += sizeof(glm::vec3);
    }

    // ������ȭ �޼���
    void deserializePlayer(const char* buffer) {
        int offset = 0;

        // Parent_Packet�� pakcet_type ������ȭ
        memcpy(&pakcet_type, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // player_index ������ȭ
        memcpy(&player_index, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // position (glm::vec3) ������ȭ
        memcpy(&position, buffer + offset, sizeof(glm::vec3));
        offset += sizeof(glm::vec3);
    }
};