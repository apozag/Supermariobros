#pragma once

#include "Body.h"
#include "Set.h"
#include <vector>

class Goomba : public Body{
private:
	std::vector<Set*>* quadrant;
public:
	Goomba(Vector2D* pos, SDL_Renderer* rend) : Body(pos, 50, 50, rend, "goombaSpriteSheet.png", 1.0, false) { setVelX(-0.5); getSrcRect()->h = 16; getSrcRect()->w = 16; }
	void update(const double &dt);
	void render();
	void clear();
	Body* clone() { return this; }
	void applyForce(Vector2D f, const double &dt);

	void kill();

	bool collideY(Entity* obj, const double &velY);
	bool collideX(Entity* obj, const double &velX);

	void setQuadrant(std::vector<Set*>* q) { if (q != nullptr) quadrant = q; }
};