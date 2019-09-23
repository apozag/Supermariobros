#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_

#include "Vector2D.h"
#include <SDL_image.h>
#include <map>
#include "TextureManager.h"
#include "Animation.h"

class Entity {
private:
	Vector2D* pos;
	SDL_Texture* texture;
	SDL_Rect *dstRect;
	SDL_Rect* srcRect;
	SDL_Renderer *renderer;
	bool animated = false;;
	std::map<animation_type, Animation*> animations;
	double depth = 1.0f;

public:
	Entity() { pos = new Vector2D(); }
	~Entity() {}
	Entity(const int &x, const int &y) { pos->setX(x); pos->setY(y); }
	Entity(Vector2D *p, const int &w, const int &h, SDL_Renderer* rend, SDL_Texture* texture, const double depth, bool animated) { pos = new Vector2D(p); srcRect = new SDL_Rect(); dstRect = new SDL_Rect();  srcRect->x = srcRect->y = 0; srcRect->w = dstRect->w = w; srcRect->h = dstRect->h = h; dstRect->x = pos->getX(); dstRect->y = pos->getY(); renderer = rend; this->texture = texture; this->depth = depth; this->animated = animated; }
	Entity(Vector2D *p, const int &w, const int &h, SDL_Renderer* rend, const char* texture, const double depth, bool animated) { pos = new Vector2D(p); srcRect = new SDL_Rect(); dstRect = new SDL_Rect();  srcRect->x = srcRect->y = 0; srcRect->w = dstRect->w = w; srcRect->h = dstRect->h = h; dstRect->x = pos->getX(); dstRect->y = pos->getY(); renderer = rend; this->texture = TextureManager::loadTexture(texture, renderer); this->depth = depth; this->animated = animated; }

	virtual void update(const double &dt) = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
	virtual Entity* clone() = 0;

	Vector2D * getPos() { return pos; }
	void setPos(Vector2D* v) { setX(v->getX()); setY(v->getY()); }
	void setX(const double &x) { pos->setX(x); dstRect->x = x; }
	void setY(const double &y) { pos->setY(y); dstRect->y = y; }
	const double &getX() { return pos->getX(); }
	const double &getY() { return pos->getY(); }
	void setW(const int &w) { dstRect->w = w; }
	const int &getW() { return dstRect->w; }
	void setH(const int &h) { dstRect->h = h; }
	const int &getH() { return dstRect->h; }
	void setTexture(SDL_Texture *t) { texture = t; }
	void setRenderer(SDL_Renderer *r) { renderer = r; }
	SDL_Renderer *getRenderer() { return renderer; }
	SDL_Texture *getTexture() { return texture; }
	SDL_Rect *getDstRect() { return dstRect; }
	SDL_Rect *getSrcRect() { return srcRect; }
	bool isAnimated() { return animated; }
	Animation* getAnimation(animation_type at) {return animations[at];}
	void addAnimation(int frames, int speed, int w, int h, animation_type at) {
		this->animations.emplace( at, new Animation(frames, speed, w, h));
	}
	void setDepth(const double d) { depth = d; }
	const double getDepth() { return depth; }
};

#endif
