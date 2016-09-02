#include "Dice.h"

//prende in input il tipo di dadi e la quantità di volte che dovrebbero essere lanciati
//in output avremo il valore totale dei tiri di dado
int Dice::roll(int diceFaces, int rollTimes)
{
	int rollSum = 0;
	if(rollTimes > 0)
	{
		for(int i=0;i<rollTimes;i++)
			rollSum += ((rand() % diceFaces) + 1);
	}
	return rollSum;
}

