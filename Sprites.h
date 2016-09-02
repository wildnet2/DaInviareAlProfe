/********************************************************
Author: Christopher Karpyszyn
Created: Oct 8th 2007
Version 1.0

This is the Base Object class
Which contains information about anything that will be 
drawn to the map.

A child to the Object class is the Character class which
automatically creates a player when it is called.
*********************************************************/

#ifndef SPRITES_H
	#define SPRITES_H

#include "Dice.h"
#include "Inventory.h"
#include <iostream>

//These are the types of races allowed in the game
//As of October 10th only HUMAN and DWARF have been implemented
enum race {HUMAN, ELF};
enum playerClass {FIGHTER, RANGER};

// #####################################################################################################
class Object{
public:
	Object();
};


// An object that moves.
// Character defines the basic rules and attributes of Characters in the game world
class Character:public Object
{
protected:
	// abilities common to all characters: strength, dexterity, consitution, wisdom, charisma
	int str, dex, con, ite;
	char* name;
	
	// hit points, current level, speed (in tiles)
	int maxHp, hp, level, speed;

	virtual void died();

public:


	Character();
	virtual ~Character(){};

	//if your not equipped your dice rolled for hand combat
	static const int HAND_COMBAT_DICE = Dice::D3;

	//gets and sets a characters name
	char* getName();
	void setName(char*);

	//input an attribute and outputs modifier
	static int getModifier(int);

	//this rolls all abilities and gets them
	// get the sum of a number of rolls, discarding the lowest
	static int getAbilityRoll();


	//mutators
	void setStr(int);
	void setDex(int);
	void setCon(int);
	void setIte(int);
	void setAllModifiers(int, int, int, int, int, int);
	void setHp(int);
	void setMaxHp(int);
	void setLevel(int);
	void setSpeed(int);

	//accessors
	int getStr();
	int getDex();
	int getCon();
	int getIte();
	int getHp();
	int getMaxHp();
	int getLevel();
	virtual int getAC();
	virtual int rollWeaponDamage(int);
	int getSpeed();
	bool isDead();

	// accessors for modifiers
	int getStrMod();
	int getDexMod();
	int getConMod();
	int getIteMod();

	//output to console
	void showCharacter();

	//info for in game fighting mechanism
	int getInitiativeRoll();
	int getAttackBonus();
	int getBaseAttackBonus();

};
// #####################################################################################################
// class ControllableCharacter has all the information and functions for a
// character that is controlled by the player
class ControllableCharacter : public Character
{
protected:
	// how to determine a randomly rolled character ability
	static const int ABILITY_ROLL_DICE_TYPE = Dice::D6;
	static const int ABILITY_ROLL_DICE_ROLLS = 4;

	void rollStartingMoney();

	int numArrows, numBolts, numPotions;
public:

	Inventory inventory;
	Weapon *equippedWeapon;
	Armor *equippedShield, *equippedHelmet, *equippedVest;

	ControllableCharacter();
	void addItem(Item*);
	void removeItem(Item*);
	bool isEquipped(Item*);
	void unEquip(Item*);
	static int getAbilityRoll();
	void setNumArrows(int);
	void setNumBolts(int);
	void setNumPotions(int);
	int getWeaponRange();
	int getNumArrows();
	int getNumBolts();
	int getNumPotions();
	int getAC();
	int rollWeaponDamage();


};

// #####################################################################################################

// a movable object which is controlled by the computer
class Monster : public Character
{
private:
	//damage dice type associated to each monster
	int damageDiceType;

protected:
	void died();

public:

	Monster();
	Monster(int, int);

	//the different types of monsters implemented
	static const int SKELETON = 0;
	static const int GOBLIN = 2;
	static const int LIZARD = 3;

	//monster HP depends on level of monster
	int getMonsterHP(int);
	//first int is for type, second int is for level
	void createMonster(int, int);
	//name, level, speed, str, dex, con, ite, wis, cha, damageDice
	void setAllMonster(char*, int, int, int, int, int, int, int);

	int getDamageDiceType();
	void setDamageDiceType(int);
};

// #####################################################################################################

// Fighter class is the definition of a certain type of character in the game
// When calling the class, it receives a specific race type specified in the above race enumeration
class Fighter : public ControllableCharacter {
public:
	const static int FIGHTER_HP = 15;
	Fighter();
	//does the roll by default, with a given race
	Fighter(race);
	//takes the values to be added for the rolls.
	Fighter(race, int, int, int, int);
};

// Ranger class is the definition of a certain type of character in the game
// When calling the class, it receives a specific race type specified in the above race enumeration
class Ranger : public ControllableCharacter {
public:
	const static int RANGER_HP = 10;
	Ranger();
	//does the roll by default, with a given race
	Ranger(race);
	//takes the values to be added for the rolls.
	Ranger(race, int, int, int, int);
};

// #####################################################################################################

// Race specific characteristics (as defined by the d20 system)
class Race
{
public:
	static const int STR_ADJ = 0;
	static const int DEX_ADJ = 0;
	static const int CON_ADJ = 0;
	static const int ITE_ADJ = 0;

	static const int HUMAN = 0;
	static const int ELF = 2;
};

// #####################################################################################################

class HumanRace : public Race
{
public:
	static const int STR_ADJ = 1;
	static const int ITE_ADJ=2;
	static const int SPEED = 30;
};

// #####################################################################################################



class ElfRace : public Race
{
public:
	static const int DEX_ADJ = 2;
	static const int CON_ADJ = -2;
	static const int SPEED = 30;
};

// #####################################################################################################



#endif

