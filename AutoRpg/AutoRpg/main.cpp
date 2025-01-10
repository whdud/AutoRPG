#include <iostream>
#include <string>
#include <vector>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
using namespace std;


int main(void)
{
	//스마트포인터 이용?
	Character* player = new Character();
	
	//몬스터 생성
	GameManger::GetInstance()->GenerateMonster(10);
	
	//플레이어 넣어서 던전출발 ㄱㄱ
	GameManger::GetInstance()->Battle(player);

	//플레이어의 인벤토리 보는 코드
	GameManger::GetInstance()->DisplayInventory(player);
	return 0;
}
