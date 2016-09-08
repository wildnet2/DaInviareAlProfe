#include "Inventory.h"
#include "Dice.h"
#include "Items.h"
#include "Sprites.h"
#include<iostream>
#include<math.h>
#include <time.h>
using namespace std;

int main() {

	//Creo 2 mostri nell'array enemies;

	Monster *enemies;
	int numEnemies;
	numEnemies = 2;
	enemies = new Monster[numEnemies];
	enemies[0] = Monster(Monster::SKELETON, 1);
	enemies[1] = Monster(Monster::SKELETON, 2);

	std::cout << "There are " << numEnemies << " monsters on this level\n";

	Character *character;
	//creo variabile tipo race di nome randRace e carico una razza randomizzata
	race randRace;
	randRace = static_cast<race>(rand() % ELF);

	//creo variabile tipo playerClass di nome randPlayerClass e carico una classe randomizzata

	playerClass randPlayerClass;
	randPlayerClass = static_cast<playerClass>(rand() % RANGER);

	//Creazione del personaggio in base a classe e razza;
	character=new Character[0];
	if (randPlayerClass == RANGER) {

		character[0]=Ranger(randRace);

	} else
		character[0]=Fighter(randRace);


	WeaponFactory *listWeapon;

		listWeapon->getAllWeapons();

}

