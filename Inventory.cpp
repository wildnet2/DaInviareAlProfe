#include "Inventory.h"

Inventory::Inventory() {}

void Inventory::addItem(Item* newItem)
{
	// aggiunge un oggetto alla fine del vettore
	itemStorage.push_back(newItem);
}

void Inventory::removeItem(Item *toRemove)
{
	// controllo per vedere se l'inventario è pieno
	if(!itemStorage.empty())
	{
		// trova gli oggetti da rimuovere, se presenti
		for(unsigned int i=0; i<itemStorage.size();i++)
		{
			// controlla se viene trovato l'oggetto cercato
			if(toRemove == itemStorage[i])
			{
				itemStorage.erase(itemStorage.begin()+i);
				break;
			}
		}
	}
}

int Inventory::getSize()
{
	return static_cast<int>(itemStorage.size());
}

unsigned int Inventory::getSizeU()
{
	return itemStorage.size();
}

Item* Inventory::get(unsigned int index)
{
	// garantisce che l'indice sia in un range valido
	if(index >= 0 && index < itemStorage.size())
		return itemStorage.at(index);
	return NULL;
}
