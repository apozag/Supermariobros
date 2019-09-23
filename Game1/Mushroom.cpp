#include "Mushroom.h"

void Mushroom::update(const double &dt) {
	bool collideX = false;
	bool collideY = false;
	
	for (Set* s : *quadrant) {
		if (getVelY() > 0.0 && this->collideX(s, getVelX() * dt)) {
			collideX = true;
			break;
		}
	}
	for (Set* s : *quadrant) {
		if (getVelY() > 0.0 && this->collideY(s, getVelY() * dt)) {
			collideY = true;
			break;
		}
	}
	

	if (!collideX) {
		setPos(&Vector2D(getPos()->getX() + getVelX() * dt, getPos()->getY()));
	}
	else {
		setVelX(getVelX() * -1);
	}
	if (!collideY) {
		setPos(&Vector2D(getPos()->getX(), getPos()->getY() + getVelY() * dt));
	}
	else {
		setVelY(0.0f);
	}
}


void Mushroom::render() {
	SDL_RenderCopy(getRenderer(), getTexture(), NULL, getDstRect());
}

void Mushroom::clear() {

}

void Mushroom::applyForce(Vector2D f, const double &dt) {
	setVel(&(*getVel() + f));
}

void Mushroom::pickup() {

}

//AABB collision
bool Mushroom::collideX(Entity* obj, const double &velX) {


	//player corners updated
	Vector2D tl = Vector2D(getX() + velX, getY());
	Vector2D tr = Vector2D(getX() + getW() + velX, getY());
	Vector2D br = Vector2D(getX() + getW() + velX, getY() + getH());
	Vector2D bl = Vector2D(getX() + velX, getY() + getH());

	//object corners
	double top = obj->getY();
	double bottom = obj->getY() + obj->getH();
	double left = obj->getX();
	double right = obj->getX() + obj->getW();

	if ((tl.getX() >= left && tl.getX() <= right) && (tl.getY() <= bottom && tl.getY() >= top)) {
		return true;
	}
	else if ((tr.getX() >= left && tr.getX() <= right) && (tr.getY() <= bottom && tr.getY() >= top)) {
		return true;
	}
	else if ((bl.getX() >= left && bl.getX() <= right) && (bl.getY() <= bottom && bl.getY() >= top)) {
		return true;
	}
	else if ((br.getX() >= left && br.getX() <= right) && (br.getY() <= bottom && br.getY() >= top)) {
		return true;
	}
	return false;

}

//AABB collision
bool Mushroom::collideY(Entity* obj, const double &velY) {

	//player corners updated
	Vector2D tl = Vector2D(getX(), getY() + velY);
	Vector2D tr = Vector2D(getX() + getW(), getY() + velY);
	Vector2D br = Vector2D(getX() + getW(), getY() + getH() + velY);
	Vector2D bl = Vector2D(getX(), getY() + getH() + velY);

	//object corners
	double top = obj->getY();
	double bottom = obj->getY() + obj->getH();
	double left = obj->getX();
	double right = obj->getX() + obj->getW();


	if ((tl.getX() >= left && tl.getX() <= right) && (tl.getY() <= bottom && tl.getY() >= top)) {
		return true;
	}
	else if ((tr.getX() >= left && tr.getX() <= right) && (tr.getY() <= bottom && tr.getY() >= top)) {
		return true;
	}
	else if ((bl.getX() >= left && bl.getX() <= right) && (bl.getY() <= bottom && bl.getY() >= top)) {
		return true;
	}
	else if ((br.getX() >= left && br.getX() <= right) && (br.getY() <= bottom && br.getY() >= top)) {
		return true;
	}
	return false;

}