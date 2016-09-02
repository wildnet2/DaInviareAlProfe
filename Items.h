#ifndef ITEMS_H
	#define ITEMS_H

#include "Dice.h"


// #####################################################################################################

/* Class Item: un elemento generico che ha un costo al momento dell'acquisto
 */
class Item
{
public:
	Item(char*);
	virtual~Item(){};

	// nome dell'oggetto, necessario se la rappresentazione grafica non è chiara
	char* name;

	//se l'oggetto è unico o no, o se ha un inventario (ex: molte pozioni, una spada)
	virtual bool isItemOfQuantity();
};

// #####################################################################################################

/* Class UsableItem: un elemento generico che può essere utilizzato(consumato). Ad esempio, questo include
 *   potions, arrows, bolts.
 */
class UsableItem : public Item
{
protected:
	// quanti di questi oggetti ci sono?
	int num;
public:
	// che tipo di materiale di consumo è questo? saranno necessari per le armi che richiedono materiali di consumo
	enum UsableItemType { ARROW, BOLT, POTION, NONE };
	UsableItemType usableType;

	UsableItem(char*, UsableItemType, int = 0);
	virtual bool isItemOfQuantity();

	// aggiunge più quantità di questo prodotto
	void add(int);

	// c'è nessun articolo a sinistra di questo tipo?
	bool isEmpty();

	// ritorna il numero di elementi a sinistra
	int numLeft();

	// usa un oggetto
	void useOne();
};

// #####################################################################################################

/* Class Potion: un oggetto utilizzabile che può essere preso per guarire un personaggio
 *   e i suoi punti ferita.
 */
class Potion : public UsableItem
{
private:
	// quanti HP restituisce questa pozione?
	int hpBonus;
public:
	Potion(char*,int,int);
	int getHpBonus();
};

// #####################################################################################################

/* Class UsableItemFactory: crea un numero finito di elementi che saranno
 *  disponibili in tutto il gioco. Esisterà solo una serie di elementi finiti
 *  e ha questa classe la responsabilità di trasmettere l'insieme di tali elementi  .
 */
class UsableItemFactory
{
private:
	// l'unico set di elementi per la maggior parte del gioco
	static UsableItem* availableUsableItems[];
	static int numAvailableUsableItems;
public:
	static UsableItem** getAllUsableItems();
	static int getNumUsableItems();
};

// #####################################################################################################

/* Class EquipableItem: un tipo di elemento che puo essere indossato, tipicamente per la battaglia
 */
class EquipableItem : public Item
{
public:
	// per mostrare le differenza con gli oggetti equipaggiabili(equipableitem)
	enum EquipableItemType { HEAD, CHEST, WEAPON, SHIELD };
	EquipableItemType equipType;
	EquipableItem(char*,EquipableItemType);
	virtual ~EquipableItem(){};
};

// #####################################################################################################

/* Class Armor: un tipo di elemento equipaggiabile che aumenta la difesa del personaggio che lo indossa
 */
class Armor : public EquipableItem
{
private:
	const int ARMOR_BONUS;
	const int MAX_DEX_BONUS;
	const int ARMOR_CHECK_PENALTY;
public:
	// nome, armatura bonus, max dex bonus,penalità armatura, costo in oro, graphicOffset, itemType
	Armor(char*,int,int,int,EquipableItemType);
	virtual ~Armor(){};
	int getArmorBonus();
	int getMaxDexBonus();
	int getArmorCheckPenalty();
};

// #####################################################################################################

/* Class ArmorFactory: crea un numero finito di armature che saranno
 *   disponibili in tutto il gioco. Esisterà solo un tipo di armatura finita
 *   ed è responsabilità di questa classe passare quelle armature
 */
class ArmorFactory
{
private:
	static Armor* availableArmor[];
	static int numAvailableArmor;
public:
	static Armor** getAllArmor();
	static int getNumArmor();
};

// #####################################################################################################

/* Class Weapon: ogni tipo di arma (sia a lungo raggio che da mischia).
 * un set di armi verrà predefinito e verrà usato in tutto il gioco
 */
class Weapon : public EquipableItem
{
private:
	const int DAMAGE_DICE_TYPE;
	const int CRITICAL_MULTIPLIER;
public:
	UsableItem::UsableItemType requiredConsumable;
	// nome, danno tipo dado, moltiplicatore critico, costo in oro, graphicOffset
	Weapon(char*,int,int);

	// nome, danno tipo dado, moltiplicatore critico, costo in oro, graphicOffset, range, requiredItem
	Weapon(char*,int,int,UsableItem::UsableItemType);
	virtual ~Weapon(){};

	char* getName();
	int getDamage();
	int getCriticalMultiplier();
};

// #####################################################################################################

/* Class WeaponFactory: crea un numero finito di armi che saranno
 *   disponibili in tutto il gioco. solo un set di armi finite esisterà
 *   ed è questa classe che ha la responasibilità di trasmetterle.
 */
class WeaponFactory
{
private:
	static Weapon* availableWeapons[];
	static int numAvailableWeapons;
public:
	static Weapon** getAllWeapons();
	static int getNumWeapons();
};

// #####################################################################################################

#endif
