#pragma once
#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <SDL.h>
class Player;
class Scene;
#include "Player.h"
#include "Set.h"
#include "Camera.h"
#include "Scene.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Goomba.h"


class Game {
private:
	bool isRunning;
	int width;
	int height;
	short key;
	SDL_Event event;
	const Uint8* keystates;
	SDL_Renderer* renderer;
	SDL_Window* window;
	Player* player;
	std::vector<Coin*> coins;
	std::vector<Mushroom*> mushrooms;
	std::vector<Goomba*> goombas;
	std::vector<Set*> background;
	Camera* camera;
	Scene* scene;
	Vector2D gravity;

public:
	Game() {}
	~Game() {}
	void init(const char* title, int xpos, int ypos, int width, int height, bool flag);
	void setGravity(Vector2D g);
	void loadLevel(int level);
	void update(const double &dt);
	void render();
	void handleEvents(const double &dt);
	void checkCoinsCollision();
	void checkMushroomCollision();
	void checkGoombaCollision();
	void checkGoombaKill();
	void clear();

	const bool running() { return isRunning; }

	void addMushroom(Mushroom* m) { mushrooms.push_back(m); }
	void addGoomba(Goomba* g) { goombas.push_back(g); }

	Scene* getScene() { return scene; }

	friend void initObjects(Game *game);
};

#endif