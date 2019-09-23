#pragma once
#ifndef SET_H_
#define SET_H_

#include "Entity.h"

enum block_type {
	BRICK,
	FLOOR,
	QUESTION,
};

class Set : public Entity{
	block_type type = FLOOR;
	Vector2D pos0;
	bool hit = false;
	unsigned int id;
public:
	Set(){}
	~Set(){}
	Set(Vector2D *p, const int &w, const int &h, SDL_Renderer* rend, const char* texture, const double depth) : Entity(p, w, h, rend, texture, depth, false), pos0(*p), id(id){}
	Set(Set *s) { setPos(new Vector2D(s->getPos()));  setW(s->getW()); setH(s->getH()); setRenderer(s->getRenderer()); setTexture(s->getTexture()); }

	Set *clone() { return new Set(this); }

	void update(const double & dt);
	void render();
	void clear();

	void setType(block_type t) { type = t; }
	const block_type getType(){ return type; }

	Vector2D getPos0() { return pos0; }

	void setHit() { hit = true; }
	const bool isHit() { return hit; }

	const unsigned int &getId() { return id; }
};

#endif