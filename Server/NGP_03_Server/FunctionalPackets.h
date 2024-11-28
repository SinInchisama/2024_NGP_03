#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "Public.h"

void EventMovePlayer(Player* p, KeyInput& k)
{
	// ���� �۾�: Player�� Action �� ����, Player�� Calculate_Move() ȣ��
	p->Set_Action(k);
	p->Calculate_Move();
}

void EventCreateItem(Item* itemArr)
{
	// �����ϴ� �۾�: Init�س��� �������� View�� Ȱ��ȭ�Ѵ�. 
	// �ʿ��� ����: ���� �������� ��ǥ, ���� �������� ���� -> Init�� �� ��������. 

	bool item_created = false;
	for (int i = 0; i < 20; ++i) {
		if (itemArr[i].View == false) {
			itemArr[i].View = true;
			// ��򰡷� ���� ������ �ʿ��ϴٸ� ���⼭ ó��
			item_created = true;
			break;
		}
	}
	
	if (!item_created)
		std::cout << "#EventCreateItem failed: can't activate item.\n";

	// ���Ŀ� Ŭ���̾�Ʈ�� ������ ����: ������ �ε���(������ ������), ����(������ ������), ��ǥ
}