#include <iostream>
#include "GameManager.h"
GameManger::GameManger()
{
	std::cout << "게임 매니저 실행 테스트..." << std::endl;
}

GameManger::~GameManger()
{
}

void GameManger::SetPlayer(Character* player)
{
	mMyCharPtr = player;
}

Monster* GameManger::GenerateMonster(int level)
{
	return nullptr;
}
void GameManger::Battle(Character* player)
{

}

void GameManger::DisplayInventory(Character* player)
{
}
