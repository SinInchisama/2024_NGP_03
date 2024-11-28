#pragma once
#include "CPlayer.h"
#include "CItem.h"
#include "Public.h"

void EventMovePlayer(Player* p, KeyInput& k)
{
	// 수행 작업: Player의 Action 값 수정, Player의 Calculate_Move() 호출
	p->Set_Action(k);
	p->Calculate_Move();
}

void EventCreateItem(Item* itemArr)
{
	// 수행하는 작업: Init해놓은 아이템의 View를 활성화한다. 
	// 필요한 정보: 만들 아이템의 좌표, 만들 아이템의 종류 -> Init에 다 만들어놓음. 

	bool item_created = false;
	for (int i = 0; i < 20; ++i) {
		if (itemArr[i].View == false) {
			itemArr[i].View = true;
			// 어딘가로 정보 전달이 필요하다면 여기서 처리
			item_created = true;
			break;
		}
	}
	
	if (!item_created)
		std::cout << "#EventCreateItem failed: can't activate item.\n";

	// 이후에 클라이언트로 보내줄 정보: 아이템 인덱스(순서로 추정됨), 색깔(종류로 추정됨), 좌표
}