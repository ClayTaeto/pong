#include "Game.h"

int Game::blueScore = 0;
int Game::redScore = 0;


//TODO: Switch over to virtual functions & just call update();
void Game::handleState() {
	switch (state) {
		case STATE_MENU: 
			//if keys, then 
			//state = STATE_PLAYING
			break;
		case STATE_PLAYING:
			//draw everything
			//check score
			if (blueScore > 9 || redScore > 9) {
				//transition into game over state
				state = STATE_GAMEOVER;
			}
			break;
		case STATE_GAMEOVER:
			break;
	}
}

void Game::reset() {
	blueScore = 0;
	redScore = 0;
}