#pragma once
typedef enum {
	KEY_UP = 0x01, // UP Ű
	KEY_DOWN = 0x02, // DOWN Ű
	KEY_LEFT = 0x04, // LEFT Ű
	KEY_RIGHT = 0x08, // RIGHT Ű
	KEY_Q = 0x10, // Q Ű (0x016 -> 0x10)
	KEY_E = 0x20, // E Ű (0x032 -> 0x20)
	KEY_A = 0x40 // A Ű (0x064 -> 0x40)
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
