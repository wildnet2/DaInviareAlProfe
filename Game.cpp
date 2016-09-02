/*
 * game.cpp
 *
 *  Created on: 25/mar/2015
 *      Author: studente
 */
#include "Character.h"
#include "Weapon.h"
#include"Sword.h"
#include <iostream>
#include"Knight.h"
#include"Bow.h"
#include"Monster.h"
#include "Tile.h"
#include"GameMap.h"
#include"Wizard.h"
#include"connectionmanager.h"
#include"ServerUnreachable.h"
#include"ServerFull.h"
int main() {

std::string serverName="dandd.game.com";
ConnectionManager cm(serverName);
try{
	cm.open();
	}catch(ServerFull & e){

	}

	GameMap* map1=new GameMap(2,2);
	Tile t1(1,true);
	Tile t2(2,false);
	Tile t3(1,true);
	Tile t4(1,true);

	map1->setTile(0, 0, t1);
	map1->setTile(0, 1, t2);
	map1->setTile(1, 0, t3);
	map1->setTile(1, 1, t4);


	GameMap map2(*map1);

	delete map1;
	map2.printMap();

	std::cout << "Monsters: " << Character::getNumMonsters() << std::endl;

	Weapon* sword = new Bow(12, 8);
	Character* hero = new Knight("Aragorn", 4);
	hero->setWeapon(sword);



	std::cout << hero << std::endl;

	Weapon* spear = new Sword(4);
	Monster orc(25, 2);
	orc.setWeapon(spear);

	std::cout << "Monsters: " << Character::getNumMonsters() << std::endl;

	int damage = hero->fight(orc);
	if (damage)
		std::cout << hero->getName() << " hits the orc - damage " << damage
				<< " hit points" << std::endl;

	Weapon* magicSword = new Sword(12, true, true);
	hero->setWeapon(magicSword);
	damage = hero->fight(orc);
	if (damage)
		std::cout << hero->getName() << " hits the orc - damage " << damage
				<< " hit points" << std::endl;

	// ...........

	delete sword;
	delete spear;
	delete magicSword;

	// ..........
}














#include "utilities.h"
#include <time.h>



int main( int argc, char *args[] )
{


	// seed rand for later use in the game
	srand ((unsigned int)time(NULL));

	//Make sure the program waits for a quit, instead of a timed exit
	bool quit = false;

	// whether or not the screen needs repainting
	bool dirty = false;

	// do the first state transition into the starting screen
	stateTransition();

	while(quit != true) 
	{

		while( SDL_PollEvent( &event ) ) 
		{
			if( event.type == SDL_KEYDOWN ) 
			{
				dirty = true;
				switch( event.key.keysym.sym ) 
				{

					case SDLK_w:
						if(state == STATE_START_SCREEN)
							startScreen->keyW();
						break;
					case SDLK_u:
						if(state == STATE_MAIN_GAME)
							mainGame->toggleUnlimitedWalking();
						break;
					case SDLK_UP:
						if(state == STATE_MAIN_GAME)
							mainGame->keyUp();
						break;
					case SDLK_DOWN:
						if(state == STATE_MAIN_GAME)
							mainGame->keyDown();
						break;
					case SDLK_LEFT:
						if(state == STATE_MAIN_GAME)
							mainGame->keyLeft();
						break;
					case SDLK_RIGHT:
						if(state == STATE_MAIN_GAME)
							mainGame->keyRight();
						break;
					default:
						break;
				}
			}
			
			if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				dirty = true;
				if( event.button.button == SDL_BUTTON_LEFT )
				{
					if (state == STATE_START_SCREEN)
						startScreen->mouseLeft(event.button.x,event.button.y);
					if (state == STATE_CHARACTER_SELECTION)
						selectionScreen->mouseLeft(event.button.x,event.button.y);
					if(state == STATE_MAIN_GAME)
						mainGame->mouseLeft(event.button.x,event.button.y);
				}
				if( event.button.button == SDL_BUTTON_RIGHT )
				{
					if (state == STATE_START_SCREEN)
						startScreen->mouseRight(event.button.x,event.button.y);
					if (state == STATE_CHARACTER_SELECTION)
						selectionScreen->mouseRight(event.button.x,event.button.y);
					if(state == STATE_MAIN_GAME)
						mainGame->mouseRight(event.button.x,event.button.y);
				}
			}

			if( event.type == SDL_QUIT ) 
			{ 
				quit = true; 
			} 

			if(isDone)
			{
				isDone = false;
				stateTransition();
			}

			if(state == STATE_GAME_EXIT)
			{
				quit = true;
			}

			// paint only if an event occured
			if(dirty)
			{
				paint();
				dirty = false;
			}
		}

		if(state == STATE_MAIN_GAME)
		{
			// send the main game ticks to move game logic (ex: AI)
			mainGame->tick();
		}

		// momentary sleep to avoid using too much CPU
		SDL_Delay(FRAME_RATE_SLEEP);
	}

	SDL_Quit();
	
	return 0;
}
