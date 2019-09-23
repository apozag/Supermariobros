#pragma once


#ifndef CAMERA_H_
#define CAMERA_H_

#include "Entity.h"
#include "Vector2D.h"

//#include "Player.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Goomba.h"
#include <vector>

class Camera {
private:
	Vector2D* pos;
	Vector2D* vel;
	Entity* follow;
public:
	Camera(Entity* e) { follow = e; pos = new Vector2D(1024/2, 768/2); vel = new Vector2D(0.0f, 0.f);}
	void setPos(Vector2D* v) { pos->setX(v->getX()); pos->setY(v->getY()); }
	void setVel(Vector2D* v) { vel->setX(v->getX()); vel->setY(v->getY()); }
	const Vector2D& getPos() { return *this->pos; }
	const Vector2D& getVel() { return *this->vel; }
	void update(const double& dt);
	void render(Entity* p, std::vector<Set*> bg, std::vector<std::vector<Set*>*>* entities, std::vector<Coin*> coins, std::vector<Mushroom*> mushrooms, std::vector<Goomba*> goombas);
};

#endif