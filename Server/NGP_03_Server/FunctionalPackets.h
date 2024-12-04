#pragma once
#include "CPlayer.h"
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

struct Create_bullet : public Parent_Packet {
    byte player_index; // 플레이어 인덱스
    bool b;        // 총알 인덱스

    // 기본 생성자
    Create_bullet() : player_index(0), b(true) {
        pakcet_type = 2; // Create_bullet의 패킷 타입 설정
    }

    // 사용자 지정 생성자
    Create_bullet(byte p_idx, bool a) : player_index(p_idx), b(a) {
        pakcet_type = 2; // Create_bullet의 패킷 타입 설정
    }

    // 직렬화 메서드
    void serialize(char* buffer) const override {
        int offset = 0;


        // Parent_Packet의 pakcet_type 직렬화
        memcpy(buffer + offset, &pakcet_type, sizeof(byte));
        offset += sizeof(byte);

        // player_index 직렬화
        memcpy(buffer + offset, &player_index, sizeof(byte));
        offset += sizeof(byte);

        // index 직렬화
        memcpy(buffer + offset, &b, sizeof(bool));
        offset += sizeof(b);
    }

    // 역직렬화 메서드
    void deserializePlayer(const char* buffer) {
        int offset = 0;

        // Parent_Packet의 pakcet_type 역직렬화
        memcpy(&pakcet_type, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // player_index 역직렬화
        memcpy(&player_index, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // index 역직렬화
        memcpy(&index, buffer + offset, sizeof(bool));
        offset += sizeof(b);
    }
};

struct Create_item : Parent_Packet {
    short item_index;
    glm::vec3 color;
    glm::vec3 locate;

    Create_item() : item_index(0), color(0.0f, 0.0f, 0.0f), locate(0.0f, 0.0f, 0.0f) {
        pakcet_type = 3;
    }

    Create_item(char i_idx, const glm::vec3& i_color, const glm::vec3& i_locate)
        : color(i_color), locate(i_locate) {
        pakcet_type = 3;
        item_index = i_idx;
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
        pakcet_type = 4;
    }

    Delete_item(const short i_idx, const glm::vec3& i_color)
        : item_index(item_index) {
        pakcet_type = 4;
        item_index = i_idx;
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

struct Change_floor : Parent_Packet {
    short box_index;
    glm::vec3 color;

    Change_floor() : box_index(0), color(0.0f, 0.0f, 0.0f) {
        pakcet_type = 6; // Move_Packet의 타입 설정
    }

    Change_floor(short b_idx, const glm::vec3& b_color)
        : box_index(b_idx), color(b_color) {
        pakcet_type = 6; // Move_Packet 타입 설정
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &box_index, sizeof(short)); offset += sizeof(short);
        memcpy(buffer + offset, &color, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }

    void deserializePlayer(const char* buffer)
    {
        int offset = 0;
        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&box_index, buffer + offset, sizeof(short)); offset += sizeof(short);
        memcpy(&color, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
    }
};

struct Move_bullet : public Parent_Packet {
    byte player_index;  // 플레이어 인덱스
    glm::vec3 position; // 총알 위치 정보

    // 기본 생성자
    Move_bullet() : player_index(0), position(0.0f, 0.0f, 0.0f) {
        pakcet_type = 7; // Move_bullet 패킷 타입 설정
    }

    // 사용자 지정 생성자
    Move_bullet(byte p_idx, const glm::vec3& pos)
        : player_index(p_idx), position(pos) {
        pakcet_type = 7; // Move_bullet 패킷 타입 설정
    }

    // 직렬화 메서드
    void serialize(char* buffer) const override {
        int offset = 0;

        // Parent_Packet의 pakcet_type 직렬화
        memcpy(buffer + offset, &pakcet_type, sizeof(byte));
        offset += sizeof(byte);

        // player_index 직렬화
        memcpy(buffer + offset, &player_index, sizeof(byte));
        offset += sizeof(byte);

        // position (glm::vec3) 직렬화
        memcpy(buffer + offset, &position, sizeof(glm::vec3));
        offset += sizeof(glm::vec3);
    }

    // 역직렬화 메서드
    void deserializePlayer(const char* buffer) {
        int offset = 0;

        // Parent_Packet의 pakcet_type 역직렬화
        memcpy(&pakcet_type, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // player_index 역직렬화
        memcpy(&player_index, buffer + offset, sizeof(byte));
        offset += sizeof(byte);

        // position (glm::vec3) 역직렬화
        memcpy(&position, buffer + offset, sizeof(glm::vec3));
        offset += sizeof(glm::vec3);
    }
};

struct Update_timer : Parent_Packet {
    short timer;

    Update_timer() : timer(0) {
        pakcet_type = 8;
    }

    Update_timer(const short G_timer)
        : timer(G_timer) {
        pakcet_type = 8;
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

struct Update_score : public Parent_Packet {
    short My_score;
    short Enermy_score;

    Update_score() : My_score(0),Enermy_score(0) {
        pakcet_type = 9;
    }

    Update_score(short my_score,short enermy_score)
        : My_score(my_score),Enermy_score(enermy_score) {
        pakcet_type = 9;
    }

    void serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &My_score, sizeof(short)); offset += sizeof(short);
        memcpy(buffer + offset, &Enermy_score, sizeof(short)); offset += sizeof(short);
    }

    void deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&My_score, buffer + offset, sizeof(short)); offset += sizeof(short);
        memcpy(&Enermy_score, buffer + offset, sizeof(short)); offset += sizeof(short);
    }
};