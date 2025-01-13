#include <iostream>
#include "Character.h"
#include "Shop.h"

int main() {

	Character player("Player", 100, 20, 50);
	Shop shop;

	player.displaystatus();

	cout << "visit shop" << endl;
	shop.DisplayItems();

	cout << "buying item" << endl;
	shop.BuyItem(0, player);

	player.displaystatus();

}