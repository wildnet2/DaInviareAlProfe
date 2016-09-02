/********************************************************
Autori: Niccolò Martini & Gabriele Vangi
Creato: 17/05/2016
Version 1.0

Questa è una semplice classe dadi.
Utilizza una chiamata a tempo macchina (time(NULL) come un seme.

DEVE SEMPRE CHIAMARE
  srand ((unsigned int)time(NULL));
prima di utilizzare la classe di dadi
*********************************************************/

#ifndef DICE_H
	#define DICE_H

#include <iostream>
#include <time.h>

// gestisce la mancanza di rand() in g++
#if defined(__MINGW32__) || defined(__MINGW64__)
    #include <cstdlib>
#else
    #include <math.h>
#endif // G++ via MinGW


//la classe di dadi non richiede variabili
//ricordarsi di chiamare srand(time(NULL));
class Dice
{
 public:
	// tutti i vari tipi di dadi
	static const int D3 = 3;
	static const int D4 = 4;
	static const int D6 = 6;
	static const int D8 = 8;
	static const int D10 = 10;
	static const int D12 = 12;
	static const int D16 = 16;
	static const int D20 = 20;

	//Tira un dado dato un certo numero di volte
	static int roll(int, int = 1);
};

#endif
