#ifndef INVENTORY_H
	#define INVENTORY_H

#include <vector>
#include "Items.h"
using std::vector;

/* Class Inventory: è una collezione di oggetti. l'inventario può essere modificato
 *   aggiungendo o rimuovendo oggetti.
 */
class Inventory
{
private:
	// insieme di elementi che vengono memorizzati
	vector<Item *> itemStorage;
public:	
	Inventory();

	// aggiunge un oggetto all'inventario
	void addItem(Item*);

	// rimuove un oggetto dall'inventario
	void removeItem(Item*);

	// il numero di oggetti che ci sono nell'inventario
	int getSize();

	// come getSize ma ritorna unsigned int
	unsigned int getSizeU();

	// restituisce un puntatore all'oggetto presente nell'inventario
	Item* get(unsigned int);
};

#endif
