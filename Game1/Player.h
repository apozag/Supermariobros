#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <algorithm>
#include <vector>

#include "Body.h"
#include "Set.h"
#include "Coin.h"


enum State {
	SMALL,
	LARGE
};


class Game;
#include "Game.h"

class Player : public Body{
private:
	Game* game;
	double MAX_VELOCITY = 2;
	bool grounded = false;
	std::vector<Set*>* quadrant;
	animation_type animationType = IDLE_RIGHT;
	bool facingRight = true;
	State state = SMALL;
public:
	Player() :Body() { }
	~Player(){}
	Player(Vector2D *p, int w, int h, SDL_Renderer* rend, const char* texture, Game* g) :Body(p, w, h, rend, texture, 1.0, true) { game = g; }
	Player(Player* p) :Player(p->getPos(), (int)p->getW(), (int)p->getH(), p->getRenderer(), "assets/walk_right.png", p->getGame()) {}
	Body* clone() { return new Player(this); }

	const bool isGrounded() {return grounded;}

	void update(const double &dt);
	void render();
	void clear();

	void applyForce(Vector2D f, const double &dt);

	bool collide(Entity* obj);

	bool collideX(Entity* obj, const double &velX);
	bool collideY(Entity* obj, const double &velY);

	void setQuadrant(std::vector<Set*>* q) { if(q != nullptr) quadrant = q; }

	
	std::vector<Set*>* getQuadrant() { return quadrant; }

	const double& getMAX_VELOCITY() { return MAX_VELOCITY; }


	void setAnimationType(animation_type at) { animationType = at;  }

	void faceRight() {facingRight = true;}
	void faceLeft() { facingRight = false; }
	const bool isFacingRight() { return facingRight; }
	const bool isFacingLeft() { return !facingRight; }

	void setState(State state) { this->state = state; }
	State getState() { return this->state; }

	Game* getGame() { return this->game; }
};


#endif
 