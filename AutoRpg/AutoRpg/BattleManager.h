#pragma once
#include <iostream>
#include <windows.h>
//#include <atomic>
#include <chrono>
#include <conio.h> 
#include <vector>

using namespace std;

class Character;
class Monster;

enum BTTSTATE
{
	EMPTY,
	READY,
	MONSTER,
	PLAYER,
	WIN,
	DIE,
	CLOSE,
};
enum CLOSESTATE
{
	cRESULT,
	cDIE,
	cWIN,
	cDELAY
};

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
public:
	void Update(Character* player, Monster* monster);
	void ReadyBattle();

	//게임중에 아이템 먹기.
	void UseItem(int item);

	void Timer();
	float GetDeltaTime();

private:
	void SetState(BTTSTATE st);
	void Ready();
	void PlayerTurn();
	void MonsterTurn();
	void PlayerWin();
	void PlayerDie();
	void Close();

	void SetSubState(int st);
	void NextGameTurn();
	void InputMsg(string str = "", bool isNewPage = false);
	int RandRange(int min , int max);
public:
	LARGE_INTEGER frequency ;
	LARGE_INTEGER cur  ;
	LARGE_INTEGER prevFrame;
	float deltaTime = 0.f;
	float fps = 0.f, fpsTime = 0.f;
	float mTime = 0.f;
	float mBattleTime = 0.f;
	int fpsCounter = 0;

private:
	vector<Monster*> mMonList;
	BTTSTATE mCurrentTurn = BTTSTATE::EMPTY;
	string mTempStr = "";
	int mState = 0;
	int mSubState = 0;
	vector<string> mStrArr;
	string mStr = "";
	Character*  mPlayer;
	Monster*	mMonster;
	int mMonsterHp = 10;
};

class BattleManager
{
};

