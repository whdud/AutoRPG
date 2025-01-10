#pragma once
/*
헤더파일 참조를 최소화 하기 위해 전방선언 했습니다.
*/
#include <vector>
class Monster;
class Character;


class GameManger
{
public:
	static GameManger* GetInstance()//&->*포인터 리턴으로 바꿨습니다.
	{
		static GameManger gm;
		return &gm;//->주소 반환 
	}

public:
	void SetPlayer(Character* player);

	//매니저에서 만드는 몬스터-> 매니저에서 관리할지
	Monster*/*주소반환*/ GenerateMonster(int level);

	//배틀관리
	void Battle(Character* player);

	//인벤토리display
	void DisplayInventory(Character* player);

public:
	GameManger();
	~GameManger();

private:
	//플레이어 관리
	Character* mMyCharPtr;
	//몬스터 벡터로 관리?
	std::vector<int> mMonsterVec;
	
};



