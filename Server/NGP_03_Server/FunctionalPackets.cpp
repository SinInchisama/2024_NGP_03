#include "FunctionalPackets.h"

void EventMovePlayer(Player* p, KeyInput& k)
{
	// ���� �۾�: Player�� Action �� ����, Player�� Calculate_Move() ȣ��
	p->Set_Action(k);
	p->Calculate_Move();
}
