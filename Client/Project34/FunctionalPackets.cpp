#include "FunctionalPackets.h"

void EventMovePlayer(Player* p, KeyInput& k)
{
	// 수행 작업: Player의 Action 값 수정, Player의 Calculate_Move() 호출
	p->Set_Action(k);
	p->Calculate_Move();		// 
}

//void EventCreateItem(Item* itemArr)
//{
//	// 수행하는 작업: Init해놓은 아이템의 View를 활성화한다. 
//	// 필요한 정보: 만들 아이템의 좌표, 만들 아이템의 종류 -> Init에 다 만들어놓음. 
//
//	bool item_created = false;
//	for (int i = 0; i < 20; ++i) {
//		if (itemArr[i].View == false) {
//			itemArr[i].View = true;
//			// 어딘가로 정보 전달이 필요하다면 여기서 처리
//			item_created = true;
//			break;
//		}
//	}
//
//	if (!item_created)
//		std::cout << "#EventCreateItem failed: can't activate item.\n";
//
//	// 이후에 클라이언트로 보내줄 정보: 아이템 인덱스(순서로 추정됨), 색깔(종류로 추정됨), 좌표
//}
//
//void EventCreateBullet(Bullet* bArr)
//{
//	bool bullet_activate = false;
//	for (int i = 0; i < 20; ++i) {
//		if (bArr[i].View == false) {
//			bArr[i].View = true;
//			// 어딘가로 정보 전달이 필요하다면 여기서 처리
//			bullet_activate = true;
//			break;
//		}
//	}
//
//	if (!bullet_activate)
//		std::cout << "#EventCreateBullet failed: can't activate bullet.\n";
//}
//
//void EventMoveBullet(Bullet* bArr)
//{
//	// TODO: 
//	// 1. 활성화된 총알을 방향과 속력에 맞춰 움직여주기
//	// 2. 맵을 벗어난 총알을 삭제하기. (여기서 할 것인가? 아니면 다른 곳(다른 이벤트, 충돌처리 등)에서 검사할 것인가? 
//}

void process_received_data(const char* buffer, size_t buffer_size, Player* p, Box All_Box[20][20]) {
    {
        // 패킷 타입 읽기
        char packet_type = buffer[0];

        // 패킷 타입에 따라 처리
        if (packet_type == 1) {
            Move_Packet packet;
            packet.deserializePlayer(buffer);
            p->Set_Move(packet.move);
            /*std::cout << "Move_Packet - Player Index: " << static_cast<int>(packet.player_index)
                << ", Move: (" << packet.move.x << ", " << packet.move.y << ", " << packet.move.z << ")\n";*/
        }
        else if(packet_type == 2) {
            Change_floor packet;
            packet.deserializePlayer(buffer);
            All_Box[packet.box_index / 20][packet.box_index % 20].Color = packet.color;
          //  std::cerr << "Unknown packet type: " << static_cast<int>(packet_type) << "\n";
        }
    }
}
