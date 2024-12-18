#include "FunctionalPackets.h"
#include "FrameWork.h"

void process_received_data(const char* buffer, size_t buffer_size, Player* p, Box All_Box[20][20],Bullet* bullet,Item* item,short& time) {
    {
        // 패킷 타입 읽기
        char packet_type = buffer[0];

        // 패킷 타입에 따라 처리
        
        if (packet_type == PACKET_MOVE_PLAYER) {
            Move_Packet packet;
            packet.deserializePlayer(buffer);
            p[packet.player_index].Set_Move(packet.move);
        }
        else if (packet_type == PACKET_CREATE_BULLET) {
            Create_bullet packet;
            packet.deserializePlayer(buffer);
            bullet[packet.player_index].View = packet.b;
        }
        else if (packet_type == PACKET_CREATE_ITEM) {
            Create_item packet;
            packet.deserializePlayer(buffer);
            item[packet.item_index].Icolor = packet.color;
            item[packet.item_index].ILocate = packet.locate;
            item[packet.item_index].View = true;
        }
        else if (packet_type == PACKET_DELETE_ITEM) {
            Delete_item packet;
            packet.deserializePlayer(buffer);
            item[packet.item_index].View = false;
        }
        else if (packet_type == PACKET_DELETE_BULLET) {
            Delete_bullet packet;
            packet.deserializePlayer(buffer);
            bullet[packet.bullet_index].View = false;
            // std::cout << "INDEX " << (int)packet.bullet_index << "'s Bullet has deleted.\n";
        }
        else if (packet_type == PACKET_CHANGE_FLOOR) {
            Change_floor packet;
            packet.deserializePlayer(buffer);
            All_Box[packet.box_index / 20][packet.box_index % 20].Color = packet.color;
            //  std::cerr << "Unknown packet type: " << static_cast<int>(packet_type) << "\n";
        }
        else if (packet_type == PACKET_MOVE_BULLET) {
            Move_bullet packet;
            packet.deserializePlayer(buffer);
            bullet[packet.player_index].Blocate = packet.position;
            std::cout << packet.position.x << "   " << packet.position.y << "   " << packet.position.z << "   " << std::endl;
        }
        else if (packet_type == PACKET_UPDATE_TIMER) {
            Update_timer packet;
            packet.deserializePlayer(buffer);
            time = packet.timer;
        }
        else if (packet_type == PACKET_UPDATE_SCORE) {
            Update_Score packet;
            packet.deserializePlayer(buffer);
            p[0].Set_Box(packet.My_score);
            p[1].Set_Box(packet.Enermy_score);
        }
        else if (packet_type == 10) {
            FrameWork::currentInstance->Exit_State();
            End_game packet;
            packet.deserializePlayer(buffer);
            Win = packet.player_index;
        }
    }
}
