#include "Items.h"


//#####################################################################################################

Item::Item(char* newName)
{
	name = newName;

}
bool Item::isItemOfQuantity()
{
	return false;
}

//#####################################################################################################

EquipableItem::EquipableItem(char* newName,EquipableItemType newEquipType) :
	Item(newName)
{
	equipType = newEquipType;
}


//#####################################################################################################

UsableItem::UsableItem(char* newName,UsableItemType newUsableType, int newNum) :
	Item(newName)
{
	usableType = newUsableType;
	num = newNum;
}

void UsableItem::add(int newAmount)
{
	if(newAmount > 0)
		num += newAmount;
}
bool UsableItem::isEmpty()
{
	return (num == 0);
}
int UsableItem::numLeft()
{
	return num;
}
void UsableItem::useOne()
{
	if(!isEmpty())
		num--;
}

bool UsableItem::isItemOfQuantity()
{
	return true;
}

//#####################################################################################################

Potion::Potion(char* newName, int graphicOffset, int newHpBonus) :
	UsableItem(newName,UsableItem::POTION,1)
{
	hpBonus = (newHpBonus>0)?newHpBonus:0;
}

int Potion::getHpBonus()
{
	if(hpBonus > 0)
		return hpBonus;
	return 0;
}

//#####################################################################################################

// crea in maniera statica l'insieme di tutti gli elementi utilizzabili nel gioco
UsableItem* UsableItemFactory::availableUsableItems[] = { 
	new UsableItem("Arrow",UsableItem::ARROW,20),
	new UsableItem("Bolt",UsableItem::BOLT,10),
	new Potion("Potion",60,5)
};

// deve corrispondere al numero di elementi creati in precedenza
int UsableItemFactory::numAvailableUsableItems = 3;


UsableItem** UsableItemFactory::getAllUsableItems()
{

}

int UsableItemFactory::getNumUsableItems()
{
	return numAvailableUsableItems;
}

//#####################################################################################################

Weapon::Weapon(char* newName, int newDamage,int newCritical) :
	DAMAGE_DICE_TYPE(newDamage), 
	CRITICAL_MULTIPLIER(newCritical),
	EquipableItem(newName,EquipableItem::WEAPON)
{
	requiredConsumable = UsableItem::NONE;
}

Weapon::Weapon(char* newName, int newDamage,int newCritical, UsableItem::UsableItemType newRequiredConsumable) :
	DAMAGE_DICE_TYPE(newDamage), 
	CRITICAL_MULTIPLIER(newCritical),
	EquipableItem(newName,EquipableItem::WEAPON)
{
	requiredConsumable = newRequiredConsumable;
}


int Weapon::getDamage()
{
	return DAMAGE_DICE_TYPE;
}

char* Weapon::getName()
{
	return name;
}


int Weapon::getCriticalMultiplier()
{
	return CRITICAL_MULTIPLIER;
}

//#####################################################################################################

Armor::Armor(char* newName, int newBonus,int newMaxDex, int newCheckPenalty, EquipableItemType newEquipableType) :
	ARMOR_BONUS(newBonus),
	MAX_DEX_BONUS(newMaxDex),
	ARMOR_CHECK_PENALTY(newCheckPenalty),
	EquipableItem(newName,newEquipableType)
{
}

int Armor::getArmorBonus()
{
	return ARMOR_BONUS;
}
int Armor::getMaxDexBonus()
{
	return MAX_DEX_BONUS;
}
int Armor::getArmorCheckPenalty()
{
	return ARMOR_CHECK_PENALTY;
}

//#####################################################################################################

// crea staticamente l'insieme di tutte le armi disponibili nel gioco
// nome, danni tipo di dado, moltiplicatore di critico, costo in oro, graphicOffset
// nome, danni tipo di dado, moltiplicatore di critico, costo in oro, graphicOffset, range, WeaponConsumable
Weapon* WeaponFactory::availableWeapons[] = { 
	new Weapon("Small Short Sword",Dice::D4,2),
	new Weapon("Medium Short Sword",Dice::D6,2),
	new Weapon("Longbow",Dice::D6,3,UsableItem::ARROW),
	new Weapon("Crossbow",Dice::D4,2,UsableItem::BOLT)
};

// deve corrispondere al numero di elementi creati in precedenza
int WeaponFactory::numAvailableWeapons = 4;


Weapon** WeaponFactory::getAllWeapons()
{

	return availableWeapons;
}

int WeaponFactory::getNumWeapons()
{
	return numAvailableWeapons;
}

//#####################################################################################################

// crea staticamente l'insieme di tutte le armi disponibili nel gioco
// (char* newName, int newBonus,int newMaxDex, int newCheckPenalty, int newCostInGold, int graphicOffset, itemType)
Armor* ArmorFactory::availableArmor[] = { 
	new Armor("Padded Light Armor",1,8,0,EquipableItem::CHEST),
	new Armor("Scale mail",4,3,-4,EquipableItem::CHEST),
	new Armor("Splint Mail",6,0,-7,EquipableItem::CHEST),
	new Armor("Basic Helm",1,0,0,EquipableItem::HEAD),
	new Armor("Buckler",1,0,-1,EquipableItem::SHIELD),
	new Armor("Heavy Steel Shield",2,0,-2,EquipableItem::SHIELD)
};

// deve corrispondere al numero di elementi creati in precenza
int ArmorFactory::numAvailableArmor = 6;


Armor** ArmorFactory::getAllArmor()
{

	return availableArmor;
}

int ArmorFactory::getNumArmor()
{
	return numAvailableArmor;
}
