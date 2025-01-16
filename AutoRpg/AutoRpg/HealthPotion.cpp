#include "HealthPotion.h"
#include "defines.h"
#include <iostream>

using namespace std;

HealthPotion::HealthPotion(int price, int healthrestore) : Item("Health Potion", price), mHealthRestore(healthrestore){}

void HealthPotion::Use(TSharedRef<Character>  character) {

	
	character.IncreaseHealth(50);

}