#pragma once

#include <vector>
#include "Set.h"
#include "Body.h"

class Mushroom : public Body{
private:
	std::vector<Set*>* quadrant;
public: 
	Mushroom(Vector2D* pos, SDL_Renderer* rend) : Body(pos, 50, 50, rend, "mushroom.png", 1.0, false){}
	void update(const double &dt);
	void render();
	void clear();
	Body* clone() { return this; }
	void applyForce(Vector2D f, const double &dt);

	void pickup();

	bool collideY(Entity* obj, const double &velY);
	bool collideX(Entity* obj, const double &velX);

	void setQuadrant(std::vector<Set*>* q) { if (q != nullptr) quadrant = q; }
};