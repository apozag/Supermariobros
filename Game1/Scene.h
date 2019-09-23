#pragma once
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <fstream>
#include "Set.h"
#include "Goomba.h"
#include "Game.h"
class Scene {
private:

	Game* game;

	std::vector<std::vector<Set*>*> quadrants;

	std::vector<Set*> set;

	std::vector<const double*> positions;

	SDL_Renderer* renderer;

	int width = 800;
	int height = 600;
public:
	Scene(SDL_Renderer* rend, Game* game):renderer(rend), game(game) {}
	bool loadLevel(int level);
	std::vector<Set*>* checkQuadrant(Vector2D pos);
	std::vector<std::vector<Set*>*>* getSet() { return &quadrants; }
};

#endif