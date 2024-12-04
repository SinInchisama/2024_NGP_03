#include "FunctionalPackets.h"

void EventMovePlayer(Player* p, KeyInput& k)
{
	// 수행 작업: Player의 Action 값 수정, Player의 Calculate_Move() 호출
	p->Set_Action(k);
	p->Calculate_Move();
}
