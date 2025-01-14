#include "AttackBoost.h"
#include <iostream>

using namespace std;

AttackBoost :: AttackBoost(int price, int attackincrease) : Item("Attack Boost", price), mAttackIncrease(attackincrease) {}

void AttackBoost::use(Character& character) 
{

	character.increaseAttack(10);

}