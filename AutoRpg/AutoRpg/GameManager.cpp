#include <iostream>
#include "GameManager.h"
#include "Character.h"
#include "troll.h"
GameManger::GameManger()
{
	std::cout << "게임 매니저 실행 테스트...\n" << std::endl;
}

GameManger::~GameManger()
{
}

void GameManger::SetPlayer(Character* player)
{
	std::cout << "게임 매니저 실행 테스트...\n" << std::endl;
	mMyCharPtr = player;
	std::cout << "플레이어 이름: "<<mMyCharPtr->getName() << std::endl; //플레이어 겟으로 정보 가져오기 private
}

Monster* GameManger::GenerateMonster(int level)
{
/*
	- 몬스터도 이름, 체력, 공격력을 가집니다.
	- 몬스터 스펙은 캐릭터 레벨에 비례해서 랜덤하게 생성:
	- 체력: (레벨 × 20) ~ (레벨 × 30)
	- 공격력: (레벨 × 5) ~ (레벨 × 10)

*/
	Monster* randomMonster = new Monster;
	return randomMonster;
}


void GameManger::SetMonster(Monster* monster)
{
	//현재 몬스터에 등록 
	mMonster = monster;
}

Monster* GameManger::GetMonster()
{
	return nullptr;
}


void GameManger::Battle(Character* player)
{
	//배틀로직 
	//턴제로 매니저에서 싸움
	


	//상점으로 갈래? 
	//스킵

}

void GameManger::DisplayInventory(Character* player)
{
}