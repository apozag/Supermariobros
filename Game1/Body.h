#pragma once
#ifndef BODY_H_
#define BODY_H_

#include "Entity.h"

class Body : public Entity {
private:
	Vector2D *vel;
	Vector2D *acceleration;
public:
	Body() :Entity() { vel = new Vector2D(); acceleration = new Vector2D(); }
	~Body(){}
	//Body(Vector2D *p, const int &w, const int &h, SDL_Renderer* rend, const char* texture, const double depth) :Entity(p, w, h, rend, texture, depth) { vel = new Vector2D(); acceleration = new Vector2D(); }
	Body(Vector2D *p, const int &w, const int &h, SDL_Renderer* rend, SDL_Texture* texture, const double depth, bool animated) :Entity(p, w, h, rend, texture, depth, animated) { vel = new Vector2D(); acceleration = new Vector2D(); }
	Body(Vector2D *p, const int &w, const int &h, SDL_Renderer* rend, const char* texture, const double depth, bool animated) :Entity(p, w, h, rend, texture, depth, animated) { vel = new Vector2D(); acceleration = new Vector2D(); }
	Body(Body *b) :Body(b->getPos(), b->getW(), b->getH(), b->getRenderer(), b->getTexture(), b->getDepth(), b->isAnimated()) {}
	virtual Body *clone() = 0;

	virtual void update(const double &dt) = 0;
	virtual void render() = 0;
	virtual void clear() = 0;

	virtual void applyForce(Vector2D f, const double &dt) {
		setVel(&(*getVel() + f));
	}
	;

	void setVel(Vector2D *v) { vel->setX(v->getX()); vel->setY(v->getY()); }
	void setVelX(double x) { vel->setX(x); }
	void setVelY(double y) { vel->setY(y); }
	Vector2D *getVel() { return vel; }
	const double &getVelX() { return vel->getX(); }
	const double &getVelY() { return vel->getY(); }

	void setAcceleration(Vector2D *v) { acceleration = new Vector2D(v); }
	void setAccelerationX(double x) { acceleration->setX(x); }
	void setAccelerationY(double y) { acceleration->setY(y); }
	Vector2D *getAcceleration() { return acceleration; }
	const double &getAccelerationX() { return acceleration->getX(); }
	const double &getAccelerationY() { return acceleration->getY(); }
};

#endif
