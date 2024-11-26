#pragma once

#define byte char

typedef enum {
	KEY_UP = 0x01, // UP 키
	KEY_DOWN = 0x02, // DOWN 키
	KEY_LEFT = 0x04, // LEFT 키
	KEY_RIGHT = 0x08, // RIGHT 키
	KEY_Q = 0x10, // Q 키 (0x016 -> 0x10)
	KEY_E = 0x20, // E 키 (0x032 -> 0x20)
	KEY_A = 0x40 // A 키 (0x064 -> 0x40)
} KeyInput;

typedef enum {
	PACKET_MOVE_PLAYER = 0x01, // Move_Player
	PACKET_CREATE_BULLET = 0x02, // Create_bullet
	PACKET_CREATE_ITEM = 0x03, // Create_Item
	PACKET_DELETE_ITEM = 0x04, // Delete_Item
	PACKET_DELETE_BULLET = 0x05, // Delete_bullet
	PACKET_CHANGE_FLOOR = 0x06, // Change_floor
	PACKET_MOVE_BULLET = 0x07, // Move_bullet
	PACKET_UPDATE_TIMER = 0x08, // Update_timer
	PACKET_UPDATE_SCORE = 0x09 // Update_score
} PacketType;

typedef struct playerInput {
	byte p_index; // - 플레이어 1인지 2인지 구분(1 or 2)
	byte input_key; // - 1 ~ 7 입력된 키 정보
} playerInput;
