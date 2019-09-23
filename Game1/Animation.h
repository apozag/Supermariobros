#pragma once

#ifndef ANIMATION_H_
#define ANIMARION_H_

#include <SDL.h>
#include "Vector2D.h"

enum animation_type {
	WALK_RIGHT,
	WALK_LEFT,
	IDLE_RIGHT,
	IDLE_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT
};

class Animation {
public:
	int frames;
	int speed;
	int w;
	int h;

	Animation(int frames, int speed, int w, int h) {
		this->frames = frames;
		this->speed = speed;
		this->w = w;
		this->h = h;
	}
};

#endif