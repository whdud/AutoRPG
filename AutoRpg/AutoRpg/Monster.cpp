#include "Monster.h"
#include <iostream>

using namespace std;

Monster::Monster(int level)
{
    mMonsterHp = rand() % (level * 10) + (level * 20); // 체력 설정
    mAttack = rand() % (level * 5) + (level * 5);   // 공격력 설정
}

string Monster::GetName() const { return mName; }
int Monster::GetMonsterHp() const { return mMonsterHp; }
int Monster::GetAttack() const { return mAttack; }
void Monster::TakeDamage(int damage) { mMonsterHp -= damage; }

void Monster::DropItem(Character& character)
{

    // if monster is not died return

    //  item drop 30%
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<>dist(1, 100);
    int DropPercent = dist(gen);

    if (DropPercent <= 30)
    {

        uniform_int_distribution<> ItemDist(1, 2);
        int ItemType = ItemDist(gen);

        shared_ptr<Item> DroppedItem;
        if (ItemType == 1)
        {

            DroppedItem = make_shared<HealthPotion>(10, 50);

        }
        else if (ItemType == 2)
        {

            DroppedItem = make_shared<AttackBoost>(20, 10);

        }

        character.AddItem(DroppedItem);
        cout << "Monster dropped Item : " << DroppedItem->GetName() << endl;

    }
}