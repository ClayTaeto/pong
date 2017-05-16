#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "cleanup.h"
#include "Sprite.h"
//#include "Ball.cpp"

int main(int, char**) {
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("pingpongpong", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);//SDL_WINDOW_FULLSCREEN);
	if (window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	//hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}	

	MSprite background("img/background.png", renderer);
	MSprite pipe("img/pipe.png", renderer);
	pipe.x = 316;
	pipe.y = 14;

	MSprite redCounter("img/0.png", renderer);
	redCounter.x = 259;
	redCounter.y = 30;

	MSprite blueCounter("img/0.png", renderer);
	blueCounter.x = 335;
	blueCounter.y = 30;

	Ball ball("img/ballBlue.png", renderer);
	ball.x = 321;
	ball.y = 230;

	CpuPaddle paddleRed("img/paddleRed.png", renderer);
	paddleRed.x = 18;
	paddleRed.y = 201;
	paddleRed.setTarget(&ball);

	MyPaddle paddleBlue("img/paddleBlu.png", renderer);
	paddleBlue.x = 604;
	paddleBlue.y = 201;

	ball.colliders.push_back(&paddleBlue);
	ball.colliders.push_back(&paddleRed);
	
	const Uint8 * keys = SDL_GetKeyboardState(NULL);
	
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		//Event Polling?
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}			
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		

		//Rendering
		SDL_RenderClear(renderer);
		

		//Draw the images
		background.draw();
		pipe.draw();
		redCounter.draw();
		blueCounter.draw();
		paddleBlue.draw();
		paddleRed.draw();
		ball.draw();

		ball.move();
		paddleRed.move();
		//dis is better
		if (keys[SDL_SCANCODE_UP]) {
			paddleBlue.moveUp();
		}

		if (keys[SDL_SCANCODE_DOWN]) {
			paddleBlue.moveDown();
		}
		
		//Update the screen
		SDL_RenderPresent(renderer);
	}
	//Clean up
	background.clean();
	paddleBlue.clean();
	paddleRed.clean();
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}