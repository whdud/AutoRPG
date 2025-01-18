#pragma once
/*
헤더파일 참조를 최소화 하기 위해 전방선언 했습니다.
*/
class Monster;
class Character;

class GameManager
{
public:
	static GameManager* GetInstance()//&->*포인터 리턴으로 바꿨습니다.
	{
		static GameManager gm;
		return &gm;//->주소 반환 
	}
public:
	void SetPlayer(Character* player);

	//매니저에서 만드는 몬스터-> 매니저에서 관리할지
	Monster*/*주소반환*/ GenerateMonster(int level);
	
	//몬스터 주소 얻어오기
	Monster* GetMonster();

public:
	GameManager();
	~GameManager();

private:
	//플레이어 관리
	Character* mMyCharPtr = nullptr;
	//몬스터 벡터로 관리?
	//std::vector<int> mMonsterVec;
	Monster* mMonster = nullptr;
};



