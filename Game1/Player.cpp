#include "Player.h"


double clamp(double value, double min, double max) {
	return std::max(std::min(value, max), min);
}

void Player::update(const double &dt) {

	//is the player going to collide if the current velocity is added?

	bool collideX = false;
	bool collideY = false;
	//x axis collision
	for (Set* s : *quadrant) {
		if (this->collideX(s, getVelX() * dt)) {
			collideX = true;
			break;
		}
	}	
	//y axis collision
	for (unsigned int i = 0; i < quadrant->size(); i++){
		if (this->collideY((*quadrant)[i], getVelY() * dt)) {
			collideY = true;
			//if it´s a question block and we are going up, it spits out something. Only if its the first time.
			if ((*quadrant)[i]->getType() == QUESTION && !(*quadrant)[i]->isHit() && getVelY() < 0.0f) {
				(*quadrant)[i]->setHit();

				Mushroom* m = new Mushroom(new Vector2D((*quadrant)[i]->getPos()), getRenderer());

				m->setVelY(-5.0);
				m->setVelX(((rand() % 2) * 2 - 1) * 0.5);

				game->addMushroom(m);
				
			}
			//if its a brick block and we are going up, it just disappears
			else if ((*quadrant)[i]->getType() == BRICK && getVelY() < 0.0f) {
				quadrant->erase(quadrant->begin() + i);
				//game->getScene()->getSet()->erase(std::remove_if(game->getScene()->getSet()->begin(), game->getScene()->getSet()->end(), [](Set*s) {s->getId() == i; }, game->getScene()->getSet()->end());
			}
			
			break;
		}
	}

	//x and y positions are only updated if its not colliding in that axis. 
	//if it is colliding, we set velocity in that axis to zero.
	if (!collideX) {
		setPos(&Vector2D(getPos()->getX() + getVelX() * dt, getPos()->getY()));
	}
	else {
		setVelX(0.0f);
	}
	if (!collideY) {
		setPos(&Vector2D(getPos()->getX(), getPos()->getY() + getVelY() * dt));
		grounded = false;
	}
	else {
		setVelY(0.0f);
		grounded = true;
	}


	//Animation selection
	if (!isGrounded()) {
		if (isFacingRight())
			setAnimationType(JUMP_RIGHT);
		else
			setAnimationType(JUMP_LEFT);
	}
	else if (getVelX() == 0) {
		if (isFacingRight())
			setAnimationType(IDLE_RIGHT);
		else
			setAnimationType(IDLE_LEFT);
	}
	else if (isFacingRight())
		setAnimationType(WALK_RIGHT);
	else
		setAnimationType(WALK_LEFT);

}

void Player::render() {
	//uses a specific row of the spritesheet depending on state and animationType
	if (isAnimated()) {

		int yoffset = 0; 

		switch (state) {
		case SMALL:
			yoffset = 0;
			getSrcRect()->w = 16;
			getSrcRect()->h = 16;
			getDstRect()->h = 50;
			break;
		case LARGE:
			yoffset= 16 * 6;
			getSrcRect()->w = 17;
			getSrcRect()->h = 32;
			getDstRect()->h = 100;
		}

		switch (animationType) {
		case WALK_RIGHT:
			getSrcRect()->y = getSrcRect()->h + yoffset;
			break;
		case WALK_LEFT:
			getSrcRect()->y = 0 + yoffset;
			break;
		case IDLE_RIGHT:
			getSrcRect()->y = getSrcRect()->h * 2 + yoffset;
			break;
		case IDLE_LEFT:
			getSrcRect()->y = getSrcRect()->h * 3 + yoffset;
			break;
		case JUMP_RIGHT:
			getSrcRect()->y = getSrcRect()->h * 5 + yoffset;
			break;
		case JUMP_LEFT:
			getSrcRect()->y = getSrcRect()->h * 4 + yoffset;
			break;
			
		}
		getSrcRect()->x = getSrcRect()->w * static_cast<int>((SDL_GetTicks() / getAnimation(animationType)->speed) % getAnimation(animationType)->frames);
	}
	SDL_RenderCopy(getRenderer(), getTexture(), getSrcRect(),getDstRect());
}

void Player::clear() {
}

void Player::applyForce(Vector2D f, const double &dt) {
	setVel(&(*getVel() + f));
}

//AABB collision
bool Player::collide(Entity* obj) {
	//player corners updated
	Vector2D tl = Vector2D(getX(), getY()) + getVel();
	Vector2D tr = Vector2D(getX() + getW(), getY()) + getVel();
	Vector2D br = Vector2D(getX() + getW(), getY() + getH()) + getVel();
	Vector2D bl = Vector2D(getX(), getY() + getH()) + getVel();

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
//use for x axis collisions only
bool Player::collideX(Entity* obj, const double &velX) {
	

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
//use for y axis collisions only
bool Player::collideY(Entity* obj, const double &velY) {
	
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
