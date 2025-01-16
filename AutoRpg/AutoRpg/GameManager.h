#pragma once
/*
헤더파일 참조를 최소화 하기 위해 전방선언 했습니다.
*/
#include "defines.h"
#include <vector>
class Monster;
class Character;
class BattleManager;

class GameManger
{
public:
	/*
	데이터 영역에 GameManager 객체를 만든것
	이 객체의 멤버함수에 접근하려면 
	GameManger::GetInstance()->를 통해 이 객체에서 멤버함수 부를수있다!
	*/
	static GameManger* GetInstance()//&->*포인터 리턴으로 바꿨습니다.
	{
		static GameManger gm;
		return &gm;//->주소 반환 
	}

public:
	void SetPlayer(TSharedPtr<Character> player);

	//매니저에서 만드는 몬스터-> 매니저에서 관리할지
	TSharedPtr<Monster>/*주소반환*/ GenerateMonster(int level);


	//배틀관리
	int Battle(TSharedPtr<Character> player);
	void StartBattle();
	//인벤토리display
	void DisplayInventory(TSharedPtr<Character>  player);

	//게임 매니저에 몬스터 넣기
	void SetMonster(TSharedPtr<Monster>monster);


	//몬스터 주소 얻어오기
	TSharedPtr<Monster> GetMonster();
	void SetBattleMgr(TSharedPtr<BattleManager>  bttmgr);

public:
	GameManger();
	~GameManger();

private:
	//플레이어 관리
	TSharedPtr<Character> mMyCharPtr = nullptr;
	//몬스터 벡터로 관리?
	//std::vector<int> mMonsterVec;
	TSharedPtr<Monster> mMonster = nullptr;
	TSharedPtr<BattleManager>battleMgr = nullptr;
};



