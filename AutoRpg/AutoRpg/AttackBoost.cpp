#include "AttackBoost.h"
#include "defines.h"
#include <iostream>

using namespace std;

AttackBoost :: AttackBoost(int price, int attackincrease) : Item("Attack Boost", price), mAttackIncrease(attackincrease) {}

void AttackBoost::Use(TSharedRef<Character> character) 
{

	character.IncreaseAttack(10);

}