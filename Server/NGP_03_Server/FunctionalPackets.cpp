#include "FunctionalPackets.h"

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