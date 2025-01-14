#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>

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
    mPlayer = player;
    mMonster = monster;
    Timer();
    cout << "\033[H";
    switch (mCurrentTurn) {
        case BTTSTATE::EMPTY:
            ReadyBattle();
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
        if ( BTTSTATE::PLAYER == mCurrentTurn ) 
        {
            if (input == '1')
                UseItem(0); //Test
            else if (input == '2')
                UseItem(1); //Test
        }
        else if (BTTSTATE::CLOSE == mCurrentTurn )
        {
            if (  CLOSESTATE::cDIE == mSubState)//ReStartGame:A / OutGame:Q 
            {

            }
            else// CLOSESTATE::WIN  // Store:A /Mob hunting:S / Status:D 
            {  
                if (input == 'a')//
                {
                }
                else if (input == 's')
                {
                }
                else if (input == 'd')
                {
                }
            }
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
    switch (mSubState)
    {
        case 0:
            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
            {
                InputMsg("   ",true);
                InputMsg("   ");
                InputMsg("        ========== BATTLE START ==========");
                SetSubState(mSubState+1);
            }
            break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.f < mBattleTime)
            {
                InputMsg("", true);
                BTTSTATE St = BTTSTATE( RandRange(2,2) );
                SetState(St);
            }
            break;
        case 2:

            break;
    }
}

void BattleManager::Close()
{
    switch (mSubState)
    {
    case CLOSESTATE::cRESULT:
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;

            if (0 == mPlayer->getHp())
            {
                InputMsg(" ");
                InputMsg("    ====  새로하기 : A / 종료하기 : Q  ====");
                SetSubState(CLOSESTATE::cDIE);
            }
            else
            {
                InputMsg(" ");
                InputMsg("            ======  전투 종료  ======");
                InputMsg(" ");
                InputMsg("    ====  상점: A  / 몬스터 사냥: S  / 스테이터스 확인: D  ====");
                SetSubState(CLOSESTATE::cWIN);
            }
            break;
    case CLOSESTATE::cDIE:break;//Player die / delay Select Game
    case CLOSESTATE::cWIN: break;
    case CLOSESTATE::cDELAY: break;
    }
}

void BattleManager::ReadyBattle()
{
    SetState(BTTSTATE::READY);
}
 
void BattleManager::UseItem(int item)
{
    if (0 == item)
    {
        int Hp = mPlayer->getHp() + 5;
        Hp = 10 < Hp ? 10 : Hp;
        mPlayer->setHp(Hp);
        InputMsg("        Use Item Hp +5!!");
    }
    else if (1 == item)
    {
        int Power = mPlayer->getAttack() + 3;
         mPlayer->setAttack(Power);
        InputMsg("        Use Item Power +3!!");
    }
}

void BattleManager::PlayerTurn()
{
    switch (mSubState)
    {
        case 0:
        {
            if (0 == mPlayer->getHp())
            {
                SetState(BTTSTATE::DIE);
                return;
            }
            
            int randAttack = RandRange(0, 10);
            if (randAttack == 0)
                InputMsg("     플레이어 공격!, 몬스터 방어 성공!");
            else
            {
                mMonsterHp = mMonsterHp - randAttack;
                mMonsterHp = mMonsterHp < 0 ? 0 : mMonsterHp;
                InputMsg("     플레이어 공격!, 몬스터 " + to_string(randAttack) + "의 데미지를 입다.");
            }
            SetSubState(mSubState + 1);
        }break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.5f < mBattleTime)
                NextGameTurn();
        break;
    }
}

void BattleManager::MonsterTurn()
{
    switch (mSubState)
    {
        case 0:
        {
            if (0 == mMonsterHp )
            {
                SetState(BTTSTATE::WIN);
                return;
            }

            int randAttack = RandRange(0, 5);
            if (randAttack == 0) 
                InputMsg("     몬스터 공격!, 플레이어 방어 성공!");
            else
            {
                int CurHp = mPlayer->getHp() - randAttack;
                CurHp = CurHp < 0 ? 0 : CurHp;
                mPlayer->setHp(CurHp);

                InputMsg("     몬스터 공격!, 플레이어 " + to_string(randAttack) + "의 데미지를 입다.");
            }
            SetSubState(mSubState + 1);
        }break;
        case 1:
            mBattleTime += GetDeltaTime();
            if (1.5f < mBattleTime)
                NextGameTurn();
        break;
    }  
}

void BattleManager::PlayerWin()
{
    //mTempStr = "Player WIN!!";
    switch (mSubState)
    {
        case 0:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            InputMsg(" ", true);
            InputMsg(" ");
            InputMsg(" ");
            InputMsg("           ====== 플레이어 승리! ======" );
            SetSubState(mSubState + 1);
        }break;
        case 1:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            int randAttack = RandRange(0,100); //30%
            if (randAttack <= 33)
                InputMsg("           ====== 아이템 획득! ====== ");
            SetSubState(mSubState + 1);
        }break;
        case 2:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            int Gold = 10;//RandRange(10, 100);
            mPlayer->setGold(Gold);
            InputMsg("           ====== 골드/" + to_string(Gold) + " 획득! ====== ");
            SetSubState(mSubState + 1);
        }break;
        case 3:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            int Exp = 50;//RandRange(10, 100);
            mPlayer->setExperience(Exp);
            InputMsg("           ====== 경험치/" + to_string(Exp) + " 획득! ====== ");
            SetState(BTTSTATE::CLOSE);
        }break;
    }
}

void BattleManager::PlayerDie()
{
   // mTempStr = "Player DIE!!";
    switch (mSubState)
    {
        case 0:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            InputMsg(" ", true);
            InputMsg(" ");
            InputMsg(" ");
            InputMsg("           ====== 플레이어 죽다.====== ");
            SetSubState(mSubState + 1);
        }break;
        case 1:
        {
            mBattleTime += GetDeltaTime();
            if (1.f > mBattleTime)
                return;
            InputMsg(" ");
            InputMsg("             ====== GAME OVER ======" );
            SetState(BTTSTATE::CLOSE);
        }break;
    }
}



void BattleManager::SetSubState(int subSt)
{
    mBattleTime = 0.f;
    mSubState = subSt;
}

void BattleManager::NextGameTurn()
{
    BTTSTATE St = mCurrentTurn == BTTSTATE::MONSTER ? BTTSTATE::PLAYER : BTTSTATE::MONSTER;
    SetState(St);
}

void BattleManager::InputMsg(string str , bool isNewPage )
{
    //cout << "\033[H";
    //mStr = str;
    system("cls");
    if (isNewPage)
        mStrArr.clear();
    
    if(str != "")
         mStrArr.push_back(str);

    int lineMax = 15;
    int lineOver = mStrArr.size() - lineMax;
   
    for (int i = 0; i < lineOver;++i)
        mStrArr.erase(mStrArr.begin());

    for (int i = 0; i < mStrArr.size();++i)
        cout << mStrArr[i] << endl;

    int lineAdd = lineMax - mStrArr.size();
    for (int i = 0; i < lineAdd;++i)
        cout << "\n" ;

    cout << "                                                   " << endl;
    cout << "                                                   " << endl;
    cout << "===================================================" << endl;
    cout << "Name:" << mPlayer->getName() << " HP:" << mPlayer->getMaxHp() << '/' << mPlayer->getHp() << "  Gold:" << mPlayer->getGold() <<
            "  || Monster1:" << " HP:" << 10 << '/' << mMonsterHp <<  endl;
    cout << "===================================================" << endl;
    // cout << "\033[H";
     //system("cls");
}

int BattleManager::RandRange(int min, int max)
{
    srand(time(NULL));
    int RandValue = rand() % max + min;
    return RandValue;
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



