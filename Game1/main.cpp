#include <iostream>
#include <SDL.h>
#include "Game.h"
#include <SDL_image.h>



int WIDTH = 1024;//720;
int HEIGHT = 768;//348;

const double dt = 3;

int FPS = 60;

Game *game;

int main(int argc, char **argv)
{
	//constant frame rate
	double period = 1.0 / (double)FPS;
	period = period * 1000;
	int milliPeriod = (int)period;
	int sleep;

	game = new Game();

	game->init("mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
	game->setGravity(Vector2D(0.0, 0.3));
	game->loadLevel(1);


	Uint32 lastTick = SDL_GetTicks();
	Uint32 currentTick = lastTick;

	while (game->running()) {

		

		sleep = milliPeriod - (currentTick - lastTick);
		if (sleep < 0) { sleep = 0; }
		SDL_Delay(sleep);

		lastTick = SDL_GetTicks();

		game->handleEvents(dt);
		game->render();
		game->update(dt);
		

		currentTick = SDL_GetTicks();
	}

	game->clear();
	return 0;
}