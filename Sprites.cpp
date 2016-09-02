#include "Sprites.h"

Object::Object(){}
// #####################################################################################################

Character::Character() :
		Object() {
	hp = maxHp = -1;
}

void Character::setName(char* name) {
	this->name = name;
}

char* Character::getName() {
	return this->name;
}

int Character::getBaseAttackBonus() {
	return getLevel() - 1;
}

int Character::getAttackBonus() {
	return (getBaseAttackBonus() + getStrMod());
}

int Character::getInitiativeRoll() {
	return (Dice::roll(Dice::D20, 1) + getDexMod());
}

int Character::rollWeaponDamage(int diceType) {
	int damageRoll, damage;
	damageRoll = Dice::roll(diceType);
	damage = damageRoll + getStrMod();
	std::cout << "Roll Damage: Combat d " << diceType << " roll: " << damageRoll
			<< " + Strenght Mod: " << getStrMod() << " = " << damage << "\n\n";
	return damage;
}

//BEGIN MODIFIERS
void Character::setStr(int str) {
	if (str <= 0)
		this->str = 0;
	else
		this->str = str;
}
void Character::setDex(int dex) {
	if (dex <= 0)
		this->dex = 0;
	else
		this->dex = dex;
}
void Character::setCon(int con) {
	if (con <= 0)
		this->con = 0;
	else
		this->con = con;
}
void Character::setIte(int ite) {
	if (ite <= 0)
		this->ite = 0;
	else
		this->ite = ite;
}

void Character::setAllModifiers(int str, int dex, int con, int ite, int wis,
		int cha) {
	setStr(str);
	setDex(dex);
	setCon(con);
	setIte(ite);
}
void Character::setHp(int newHp) {
	if (newHp <= 0) {
		hp = 0;
		died();
	} else if (newHp > maxHp)
		hp = maxHp;
	else
		hp = newHp;
}

void Character::setMaxHp(int newMaxHp) {
	if (newMaxHp > 0)
		maxHp = newMaxHp;
}

void Character::setLevel(int level) {
	if (level <= 1)
		this->level = 1;
	else
		this->level = level;
}

void Character::setSpeed(int speedInFeet) {
	if (speedInFeet < 5)
		this->speed = 1;
	else
		this->speed = speedInFeet;
}
//END MODIFIERS

//BEGIN ACCESSORS
int Character::getStr() {
	return str;
}
int Character::getDex() {
	return dex;
}
int Character::getCon() {
	return con;
}
int Character::getIte() {
	return ite;
}
int Character::getHp() {
	return hp;
}
int Character::getMaxHp() {
	return maxHp;
}
int Character::getLevel() {
	return level;
}
int Character::getSpeed() {
	return speed;
}

int Character::getModifier(int base) {
	return (base / 2) - 5;
}

int Character::getStrMod() {
	return getModifier(str);
}
int Character::getDexMod() {
	return getModifier(dex);
}
int Character::getConMod() {
	return getModifier(con);
}
int Character::getIteMod() {
	return getModifier(ite);
}


// Armor Class (AC): How hard a character is to hit. 
// 10 + armor bonus + shield bonus + size modifier + dexterity modifier
int Character::getAC() {
	int ac = 10 + getModifier(dex);
	std::cout << "Calculate Armour Class:\n10 + Dex Modifier: "
			<< getModifier(dex) << " = " << (ac) << "\n";
	return ac;
}
//END ACCESSORS

void Character::showCharacter() {
	std::cout << "\nYour character (after Race based adjustments):\n" << "STR: "
			<< getStr() << ", Mod: " << getStrMod() << "\n" << "DEX: "
			<< getDex() << ", Mod: " << getDexMod() << "\n" << "CON: "
			<< getCon() << ", Mod: " << getConMod() << "\n" << "ITE: "
			<< getIte() << ", Mod: " << getIteMod() << "\n" << "SPEED: "
			<< getSpeed() << "\n" << "HP: " << getHp() << "\n";
}

void Character::died() {
	if (isDead()) {
		std::cout << name << " has died.\n";
		speed = 0;
	}
}

bool Character::isDead() {
	return (hp < 1);
}

// #####################################################################################################

ControllableCharacter::ControllableCharacter() :
		Character() {

	//conversion from string to constant char* about the name of item's inventory.
	char *scaleMail=(char*)"Scale mail";
    char *crossbow=(char*)"Crossbow";
    char *basicHelm=(char*)"Basic Helm";
    char *buckler=(char*)"Buckler";
    char *smallShortSword=(char*)"Small Short Sword";
    char*mainCharacter=(char*)"Main Character";
	equippedWeapon=NULL;
	equippedShield = NULL;
	equippedHelmet = NULL;
	equippedVest = NULL;

	UsableItem** tempItems = UsableItemFactory::getAllUsableItems();

	// all characters start with 0 potions, 0 arrows and 0 bolts
	numArrows = numBolts = numPotions = 0;
	inventory.addItem(tempItems[0]);
	inventory.addItem(tempItems[1]);
	inventory.addItem(tempItems[2]);
	//add armor and weapon to inventory
	inventory.addItem(new Weapon(crossbow,Dice::D4,2,UsableItem::BOLT));
	inventory.addItem(new Armor(scaleMail,4,3,-4,EquipableItem::CHEST));
	inventory.addItem(new Armor(basicHelm,1,0,0,EquipableItem::HEAD));
	inventory.addItem(new Armor(buckler,1,0,-1,EquipableItem::SHIELD));
	inventory.addItem(new Weapon(smallShortSword,Dice::D4,2));

	setName(mainCharacter);
}

int ControllableCharacter::rollWeaponDamage() {
	int damageRoll, damage;
	char* weaponName;

	if (equippedWeapon != NULL)
		damageRoll = Dice::roll(equippedWeapon->getDamage());
	else {
		damageRoll = HAND_COMBAT_DICE;
		weaponName = "Hand Combat";
	}

	damage = damageRoll + getStrMod();
	std::cout << "Roll Damage: " << weaponName << " d"
			<< equippedWeapon->getDamage() << " roll:  " << damageRoll
			<< " + Strenght Mod: " << getStrMod() << " = " << damage << "\n\n";
	return damage;
}

// Armor Class (AC): How hard a character is to hit. 
// 10 + armor bonus + shield bonus + size modifier + dexterity modifier
int ControllableCharacter::getAC() {
	int vestBonus = 0;
	int helmetBonus = 0;
	int shieldBonus = 0;
	int AC;

	if (equippedShield != NULL)
		shieldBonus = equippedShield->getArmorBonus();

	if (equippedHelmet != NULL)
		helmetBonus = equippedHelmet->getArmorBonus();

	if (equippedVest != NULL)
		vestBonus = equippedVest->getArmorBonus();

	AC = 10 + getModifier(dex) + vestBonus + helmetBonus + shieldBonus;

	std::cout << "Armor Class Calculation: \n" << "Shield Bonus: "
			<< shieldBonus << "+ Helmet Bonus: " << helmetBonus
			<< "  + Vest Bonus: " << vestBonus;
	std::cout << " + Dexterity Mod: " << getModifier(dex) << "+ 10 = " << AC
			<< "\n\n";
	return AC;
}

int ControllableCharacter::getAbilityRoll() {
	int smallestRoll = 0;
	int rollAmount;
	int runningSum = 0;

	// roll the dice a number of times, calculate the running sum and locate the smallest roll
	std::cout << "Rolling: ";
	for (int i = 0; i < ABILITY_ROLL_DICE_ROLLS; i++) {
		rollAmount = Dice::roll(ABILITY_ROLL_DICE_TYPE);
		runningSum += rollAmount;
		std::cout << rollAmount << ",";

		// track the smallest roll if it isn't the only roll to be performed
		if (i == 0 && ABILITY_ROLL_DICE_ROLLS > 1) {
			smallestRoll = rollAmount;
		} else {
			if (smallestRoll > rollAmount)
				smallestRoll = rollAmount;
		}
	}

	std::cout << " discarding: " << smallestRoll << ", total: "
			<< (runningSum - smallestRoll) << "\n";

	// discard the smallest roll and return the sum
	return (runningSum - smallestRoll);
}

void ControllableCharacter::unEquip(Item* toUnequip) {
	if (equippedHelmet == toUnequip)
		equippedHelmet = NULL;
	else if (equippedWeapon == toUnequip)
		equippedWeapon = NULL;
	else if (equippedShield == toUnequip)
		equippedShield = NULL;
	else if (equippedVest == toUnequip)
		equippedVest = NULL;
	else {
	}
}

void ControllableCharacter::addItem(Item* toAdd) {
	if (toAdd->isItemOfQuantity()) {
		UsableItem* tempUsableItem = static_cast<UsableItem*>(toAdd);
		switch (tempUsableItem->usableType) {
		case UsableItem::POTION:
			numPotions += tempUsableItem->numLeft();
			break;
		case UsableItem::ARROW:
			std::cout << "Increasing the number of arrows by "
					<< tempUsableItem->numLeft() << "\n";
			numArrows += tempUsableItem->numLeft();
			break;
		case UsableItem::BOLT:
			std::cout << "Increasing the number of bolts by "
					<< tempUsableItem->numLeft() << "\n";
			numBolts += tempUsableItem->numLeft();
			break;

		}
	} else {
		inventory.addItem(toAdd);
	}
}

void ControllableCharacter::removeItem(Item* toRemove) {
	unEquip(toRemove);
	inventory.removeItem(toRemove);
}

bool ControllableCharacter::isEquipped(Item* toFind) {
	return (equippedHelmet == toFind || equippedWeapon == toFind
			|| equippedShield == toFind || equippedVest == toFind);
}

int ControllableCharacter::getNumArrows() {
	return numArrows;
}
int ControllableCharacter::getNumBolts() {
	return numBolts;
}
int ControllableCharacter::getNumPotions() {
	return numPotions;
}

void ControllableCharacter::setNumArrows(int newNumArrows) {
	if (newNumArrows >= 0)
		this->numArrows = newNumArrows;
}
void ControllableCharacter::setNumBolts(int newNumBolts) {
	if (newNumBolts >= 0)
		this->numBolts = newNumBolts;
}
void ControllableCharacter::setNumPotions(int newNumPotions) {
	if (newNumPotions >= 0)
		this->numPotions = newNumPotions;
}

int ControllableCharacter::getWeaponRange() {
	int weaponReach = 0;
	if (weaponReach < 1)
		weaponReach = 1;
	return weaponReach;
}

// #####################################################################################################

Fighter::Fighter() {

}

//Constructor class
//Takes a type race to specify which race the character is
//Each race may have specific additions to the modifiers
//Hitpoints, Level, and AC begin at a predetermined base
//Str, Dex, Con, Ite, Wis, Cha are all determined randomly by the character roll.
Fighter::Fighter(race myrace) :
		ControllableCharacter() {

	setMaxHp(FIGHTER_HP);
	setHp(FIGHTER_HP);
	setLevel(1);

	std::cout << "\nNow rolling your abilities using a "
			<< ABILITY_ROLL_DICE_ROLLS << "d" << ABILITY_ROLL_DICE_TYPE
			<< " ...\n";

	switch (myrace) {
	case HUMAN:
		setStr(getAbilityRoll() + HumanRace::STR_ADJ);
		setDex(getAbilityRoll() + HumanRace::DEX_ADJ);
		setCon(getAbilityRoll() + HumanRace::CON_ADJ);
		setIte(getAbilityRoll() + HumanRace::ITE_ADJ);
		setSpeed(HumanRace::SPEED);
		break;
	case ELF:
		setStr(getAbilityRoll() + ElfRace::STR_ADJ);
		setDex(getAbilityRoll() + ElfRace::DEX_ADJ);
		setCon(getAbilityRoll() + ElfRace::CON_ADJ);
		setIte(getAbilityRoll() + ElfRace::ITE_ADJ);
		setSpeed(ElfRace::SPEED);
		break;
	}
}

Fighter::Fighter(race myrace, int str, int dex, int con, int ite) :
		ControllableCharacter() {

	setMaxHp(FIGHTER_HP);
	setHp(FIGHTER_HP);
	setLevel(1);

	switch (myrace) {
	case HUMAN:
		setStr(str + HumanRace::STR_ADJ);
		setDex(dex + HumanRace::DEX_ADJ);
		setCon(con + HumanRace::CON_ADJ);
		setIte(ite + HumanRace::ITE_ADJ);
		setSpeed(HumanRace::SPEED);
		break;
	case ELF:
		setStr(str + ElfRace::STR_ADJ);
		setDex(dex + ElfRace::DEX_ADJ);
		setCon(con + ElfRace::CON_ADJ);
		setIte(ite + ElfRace::ITE_ADJ);
		setSpeed(ElfRace::SPEED);
		break;
	}
}

// #####################################################################################################
Ranger::Ranger() {

}

//Constructor class
//Takes a type race to specify which race the character is
//Each race may have specific additions to the modifiers
//Hitpoints, Level, and AC begin at a predetermined base
//Str, Dex, Con, Ite, Wis, Cha are all determined randomly by the character roll.
Ranger::Ranger(race myrace) :
		ControllableCharacter() {

	setMaxHp(RANGER_HP);
	setHp(RANGER_HP);
	setLevel(1);
	std::cout << "\nNow rolling your abilities using a "
			<< ABILITY_ROLL_DICE_ROLLS << "d" << ABILITY_ROLL_DICE_TYPE
			<< " ...\n";

	switch (myrace) {
	case HUMAN:
		setStr(getAbilityRoll() + HumanRace::STR_ADJ);
		setDex(getAbilityRoll() + HumanRace::DEX_ADJ);
		setCon(getAbilityRoll() + HumanRace::CON_ADJ);
		setIte(getAbilityRoll() + HumanRace::ITE_ADJ);
		setSpeed(HumanRace::SPEED);
		break;
	case ELF:
		setStr(getAbilityRoll() + ElfRace::STR_ADJ);
		setDex(getAbilityRoll() + ElfRace::DEX_ADJ);
		setCon(getAbilityRoll() + ElfRace::CON_ADJ);
		setIte(getAbilityRoll() + ElfRace::ITE_ADJ);
		setSpeed(ElfRace::SPEED);
		break;
	}
}

Ranger::Ranger(race myrace, int str, int dex, int con, int ite) :
		ControllableCharacter() {

	setMaxHp(RANGER_HP);
	setHp(RANGER_HP);
	setLevel(1);

	switch (myrace) {
	case HUMAN:
		setStr(str + HumanRace::STR_ADJ);
		setDex(dex + HumanRace::DEX_ADJ);
		setCon(con + HumanRace::CON_ADJ);
		setIte(ite + HumanRace::ITE_ADJ);
		setSpeed(HumanRace::SPEED);
		break;
	case ELF:
		setStr(str + ElfRace::STR_ADJ);
		setDex(dex + ElfRace::DEX_ADJ);
		setCon(con + ElfRace::CON_ADJ);
		setIte(ite + ElfRace::ITE_ADJ);
		setSpeed(ElfRace::SPEED);
		break;
	}
}

// #####################################################################################################

Monster::Monster() {
}
Monster::Monster(
		int monsterType, int level) :
		Character() {

	createMonster(monsterType, level);


}

void Monster::createMonster(int monster, int level) { //name, level, speed, str, dex, con, ite, wis, cha, damageDice
	switch (monster) {
	case SKELETON:
		setAllMonster("Skeleton", level, 30, 13, 13, 0, 0, Dice::D12);
		break;

	case LIZARD:
		setAllMonster("Lizard", level, 20, 3, 15, 10, 1, Dice::D8);
		break;

	}
}

int Monster::getMonsterHP(int level) {
	if (level == 1)
		return (10);
	else
		return (10 + level * 5);
}

void Monster::setAllMonster(char* name, int level, int speed, int str, int dex,
		int con, int ite, int diceType) {
	setLevel(level);
	setMaxHp(getMonsterHP(level));
	setHp(getMonsterHP(level));
	setSpeed(speed);

	setName(name);

	setStr(str);
	setDex(dex);
	setCon(con);
	setIte(ite);

	setDamageDiceType(diceType);

}

void Monster::setDamageDiceType(int diceType) {
	this->damageDiceType = diceType;
}

int Monster::getDamageDiceType() {
	return damageDiceType;
}

void Monster::died() {
	if (isDead()) {
		Character::died();
	}
}

// #####################################################################################################

