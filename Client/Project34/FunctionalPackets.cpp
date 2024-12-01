#include "FunctionalPackets.h"

void EventMovePlayer(Player* p, KeyInput& k)
{
	// ���� �۾�: Player�� Action �� ����, Player�� Calculate_Move() ȣ��
	p->Set_Action(k);
	p->Calculate_Move();		// 
}

//void EventCreateItem(Item* itemArr)
//{
//	// �����ϴ� �۾�: Init�س��� �������� View�� Ȱ��ȭ�Ѵ�. 
//	// �ʿ��� ����: ���� �������� ��ǥ, ���� �������� ���� -> Init�� �� ��������. 
//
//	bool item_created = false;
//	for (int i = 0; i < 20; ++i) {
//		if (itemArr[i].View == false) {
//			itemArr[i].View = true;
//			// ��򰡷� ���� ������ �ʿ��ϴٸ� ���⼭ ó��
//			item_created = true;
//			break;
//		}
//	}
//
//	if (!item_created)
//		std::cout << "#EventCreateItem failed: can't activate item.\n";
//
//	// ���Ŀ� Ŭ���̾�Ʈ�� ������ ����: ������ �ε���(������ ������), ����(������ ������), ��ǥ
//}
//
//void EventCreateBullet(Bullet* bArr)
//{
//	bool bullet_activate = false;
//	for (int i = 0; i < 20; ++i) {
//		if (bArr[i].View == false) {
//			bArr[i].View = true;
//			// ��򰡷� ���� ������ �ʿ��ϴٸ� ���⼭ ó��
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
//	// 1. Ȱ��ȭ�� �Ѿ��� ����� �ӷ¿� ���� �������ֱ�
//	// 2. ���� ��� �Ѿ��� �����ϱ�. (���⼭ �� ���ΰ�? �ƴϸ� �ٸ� ��(�ٸ� �̺�Ʈ, �浹ó�� ��)���� �˻��� ���ΰ�? 
//}

void process_received_data(const char* buffer, size_t buffer_size, Player* p, Box All_Box[20][20]) {
    {
        // ��Ŷ Ÿ�� �б�
        char packet_type = buffer[0];

        // ��Ŷ Ÿ�Կ� ���� ó��
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
