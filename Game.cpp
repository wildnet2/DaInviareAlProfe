
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
