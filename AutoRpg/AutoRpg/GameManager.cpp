﻿#include <iostream>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Plumpkin.h"
#include "Buckpip.h"
#include "Jackpatch.h"
#include "Chicken.h"
#include <random>
GameManager::GameManager()
{
	std::cout << "게임 매니저 실행 테스트...\n" << std::endl;
}

GameManager::~GameManager()
{
	delete mMyCharPtr;
	if (mMonster)
		delete mMonster;
}

void GameManager::SetPlayer(Character* player)
{
	std::cout << "게임 매니저 실행 테스트...\n" << std::endl;
	mMyCharPtr = player;
	std::cout << "플레이어 이름: "<<mMyCharPtr->GetName() << std::endl; //플레이어 겟으로 정보 가져오기 private
}

Monster* GameManager::GenerateMonster(int level)
{
/*
	- 몬스터도 이름, 체력, 공격력을 가집니다.
	- 몬스터 스펙은 캐릭터 레벨에 비례해서 랜덤하게 생성:
	- 체력: (레벨 × 20) ~ (레벨 × 30)
	- 공격력: (레벨 × 5) ~ (레벨 × 10)
*/
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(0, 99);

	int randomNum =  dis(gen) % 3;
	Monster* randomMonster = nullptr;

	if (10 <= mMyCharPtr->GetLevel())
	{
		randomMonster = new Chicken(level);
		randomMonster->SetBossMonster();
	}
	else 
	{
		switch (randomNum)
		{
		case 0:
			randomMonster = new Plumpkin(level);
			break;
		case 1:
			randomMonster = new Buckpip(level);
			break;
		case 2:
			randomMonster = new Jackpatch(level);
			break;
		default:
			break;
		}
	}

	if (mMonster)
		delete mMonster;
	mMonster = randomMonster;

	return randomMonster;
}
Monster* GameManager::GetMonster()
{
	return mMonster;
}
