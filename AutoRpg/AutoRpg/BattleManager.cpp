#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include <math.h>
#include<cstdlib>
#include<ctime>


BattleManager::BattleManager()
{
    QueryPerformanceFrequency(&frequency); // 한번만 읽어들이면 된다.
    QueryPerformanceCounter(&prevFrame); // 이전틱 기억
    
}

BattleManager::~BattleManager()
{
}

void BattleManager::Update( Character* player, Monster* monster)
{
    Timer();

    switch (mCurrentTurn) {
        case BTTSTATE::EMPTY:
            break;
        case BTTSTATE::READY:
            Ready();
            break;
        case BTTSTATE::MONSTER:
            MonsterTurn();
            break;
        case BTTSTATE::PLAYER:
            PlayerTurn();
            break;
        case BTTSTATE::WIN:
            PlayerWin();
            break;
        case BTTSTATE::DIE:
            PlayerDie();
            break;
        case BTTSTATE::CLOSE:
            Close();
            break;
    }
    if (_kbhit()) {
        char input = _getch();
        if (input == '1') {
            UseItem(0); //Test
        }
        if (input == '2') {
            UseItem(1); //Test
        }
    }
}

void BattleManager::SetState(BTTSTATE st)
{
    mCurrentTurn = st;
    mSubState = 0;
    mBattleTime = 0.f;
}

void BattleManager::Ready()
{
    mBattleTime += GetDeltaTime();
    switch (mSubState)
    {
        case 0:
            if (1.f < mBattleTime)
            {
                srand(time(NULL));
                BTTSTATE St  = BTTSTATE(rand() % 2 + 1);
                SetState(St);
            }
            break;
    }
}

void BattleManager::Close()
{
    switch (mSubState)
    {
    case 0:
        cout << "Battle Close!" << endl;
        mSubState = 1;
        break;
    case 1:
        break;
    }
}

void BattleManager::StartBattle()
{
    SetState(BTTSTATE::READY);
}
 
void BattleManager::UseItem(int item)
{
    if (0 == item) //
        cout << "      Use Item Hp +5!!" << endl;
    else if (1 == item) //
        cout << "      Use Item Power +3!!" << endl;
}

void BattleManager::PlayerTurn()
{
    switch (mSubState)
    {
        case 0:
            mTempStr = "Player Attack!!";
            cout << mTempStr << endl;
            mSubState = 1;
            break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (2.f < mBattleTime)
                NextGameTurn();
            break;
    }
}

void BattleManager::MonsterTurn()
{
    switch (mSubState)
    {
        case 0:
            mTempStr = "Monster Attack!!";
            cout << mTempStr << endl;
            mSubState = 1;
            break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (2.f < mBattleTime)
                NextGameTurn();
            break;
    }  
}

void BattleManager::PlayerWin()
{
    mTempStr = "Player WIN!!";
}

void BattleManager::PlayerDie()
{
    mTempStr = "Player DIE!!";
}



void BattleManager::SetSubState(int st)
{
    mBattleTime = 0.f;
}

void BattleManager::NextGameTurn()
{
    BTTSTATE St = mCurrentTurn == BTTSTATE::MONSTER ? BTTSTATE::PLAYER : BTTSTATE::MONSTER;
    SetState(St);
}

void BattleManager::Timer()
{
    QueryPerformanceCounter(&cur); // 현재틱
    deltaTime = (cur.QuadPart - prevFrame.QuadPart) / static_cast<float>(frequency.QuadPart);
    //Time += deltaTime;
    prevFrame = cur; // 이전틱 현재틱으로 변경
    // 프레임 구하기
    ++fpsCounter;
    fpsTime += deltaTime;
    if (fpsTime >= 1.0f) // 1초가 지났다면
    {
        fps = fpsCounter; // 프레임
        fpsCounter = 0;
        fpsTime = 0.0f;
    }
    //std::cout << "프레임 :" << fps << " " << "현재시간 : ";
    //std::cout << Time << std::endl;
}
float BattleManager::GetDeltaTime()
{
    return deltaTime;
}



