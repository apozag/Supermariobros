#pragma once

#ifndef COIN_H_
#define COIN_H_

#include "Entity.h"

class Coin : public Entity{
public:
	Coin(Vector2D *p, SDL_Renderer* rend): Entity(p, 50, 50, rend, "coin.png", 1.0, false){}
	void pickup();
	void clear();
	Coin* clone() { return this; };
	void update(const double &dt) {};
	void render();
};

#endif
