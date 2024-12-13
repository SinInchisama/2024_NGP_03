#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "CBullet.h"
#include "Public.h"
#include <vector>
#include "CBox.h"

void process_received_data(const char* buffer, size_t buffer_size, Player* p, Box All_Box[20][20], Bullet* bullet, Item* item, short& time);

struct Parent_Packet {
	byte pakcet_type;

    virtual int serialize(char* buffer)const { return 0; }

    virtual ~Parent_Packet() = default;
};

struct Move_Packet : Parent_Packet {
	byte player_index;
	glm::vec3 move;

    Move_Packet() : player_index(0), move(0.0f, 0.0f, 0.0f) {
        pakcet_type = 1; // Move_Packet의 타입 설정
    }

     int serialize(char* buffer)const override{
         int offset = 0;

         memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
         memcpy(buffer + offset, &player_index, sizeof(byte)); offset += sizeof(byte);
         memcpy(buffer + offset, &move, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

         return offset;
     }

     int deserializePlayer(const char* buffer)
     {
         int offset = 0;

         memcpy(&pakcet_type,buffer + offset, sizeof(byte)); offset += sizeof(byte);
         memcpy(&player_index,buffer + offset, sizeof(byte)); offset += sizeof(byte);
         memcpy(&move,buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

         return offset;
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

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &box_index, sizeof(short)); offset += sizeof(short);
        memcpy(buffer + offset, &color, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

        return offset;
    }

    int deserializePlayer(const char* buffer)
    {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&box_index, buffer + offset, sizeof(short)); offset += sizeof(short);
        memcpy(&color, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

        return offset;
    }
};

struct Create_bullet : public Parent_Packet {
    byte player_index; // 플레이어 인덱스
    bool b;        // 총알 인덱스

    // 기본 생성자
    Create_bullet() : player_index(0), b(true) {
        pakcet_type = 3; // Create_bullet의 패킷 타입 설정
    }

    // 사용자 지정 생성자
    Create_bullet(byte p_idx, bool a) : player_index(p_idx), b(a) {
        pakcet_type = 3; // Create_bullet의 패킷 타입 설정
    }

    int serialize(char* buffer) const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &player_index, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &b, sizeof(bool)); offset += sizeof(b);

        return offset;
    }

    int deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&player_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&b, buffer + offset, sizeof(bool)); offset += sizeof(b);

        return offset;
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

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &item_index, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &color, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
        memcpy(buffer + offset, &locate, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

        return offset;
    }

    int deserializePlayer(const char* buffer)
    {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&item_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&color, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
        memcpy(&locate, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

        return offset;
    }
};

struct Delete_item : Parent_Packet {
    short item_index;

    Delete_item() : item_index(0) {
        pakcet_type = 4;
    }

    Delete_item(const short i_idx)
        : item_index(item_index) {
        pakcet_type = 4;
    }

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &item_index, sizeof(short)); offset += sizeof(short);

        return offset;
    }

    int deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&item_index, buffer + offset, sizeof(short)); offset += sizeof(short);

        return offset;
    }
};

struct Delete_bullet : Parent_Packet {
    byte bullet_index;

    Delete_bullet() :bullet_index(0) {
        pakcet_type = 5;
    }
    Delete_bullet(byte b) :bullet_index(b) {
        pakcet_type = 5;
    }

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &bullet_index, sizeof(short)); offset += sizeof(short);

        return offset;
    }

    int deserializePlayer(const char* buffer)
    {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&bullet_index, buffer + offset, sizeof(short)); offset += sizeof(short);

        return offset;
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
        pakcet_type = 4; // Move_bullet 패킷 타입 설정
    }

    int serialize(char* buffer) const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &player_index, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &position, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

        return offset;
    }

    int deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&player_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&position, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);

        return offset;
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

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &timer, sizeof(short)); offset += sizeof(short);

        return offset;
    }

    int deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&timer, buffer + offset, sizeof(short)); offset += sizeof(short);

        return offset;
    }
};

struct Update_Score : public Parent_Packet {
    short My_score;
    short Enermy_score;

    Update_Score() : My_score(0), Enermy_score(0) {
        pakcet_type = 9;
    }

    Update_Score(short my_score, short enermy_score)
        : My_score(my_score), Enermy_score(enermy_score) {
        pakcet_type = 9;
    }

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &My_score, sizeof(short)); offset += sizeof(short);
        memcpy(buffer + offset, &Enermy_score, sizeof(short)); offset += sizeof(short);

        return offset;
    }

    int deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&My_score, buffer + offset, sizeof(short)); offset += sizeof(short);
        memcpy(&Enermy_score, buffer + offset, sizeof(short)); offset += sizeof(short);

        return offset;
    }
};

struct End_game : public Parent_Packet {
    byte player_index;


    End_game() {
        pakcet_type = 10;
    }

    End_game(byte b) :player_index(b) {
        pakcet_type = 10;
    }

    int serialize(char* buffer)const override {
        int offset = 0;

        memcpy(buffer + offset, &pakcet_type, sizeof(byte)); offset += sizeof(byte);
        memcpy(buffer + offset, &player_index, sizeof(byte)); offset += sizeof(byte);
        
        return offset;
    }

    int deserializePlayer(const char* buffer) {
        int offset = 0;

        memcpy(&pakcet_type, buffer + offset, sizeof(byte)); offset += sizeof(byte);
        memcpy(&player_index, buffer + offset, sizeof(byte)); offset += sizeof(byte);

        return offset;
    }
};