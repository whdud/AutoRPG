#include "HealthPotion.h"
#include <iostream>

using namespace std;

HealthPotion::HealthPotion(int price, int healthrestore) : Item("Health Potion", price), mHealthRestore(healthrestore){}

void HealthPotion::Use(Character& character) {

	character.IncreaseHealth(50);

}