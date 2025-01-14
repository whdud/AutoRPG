#include "HealthPotion.h"
#include <iostream>

using namespace std;

HealthPotion::HealthPotion(int price, int healthrestore) : Item("Health Potion", price), mHealthRestore(healthrestore){}

void HealthPotion::use(Character& character) {

	character.increaseHealth(50);

}