#include "Camera.h"

void Camera::update(const double& dt) {
	//update velocity

	//velocity is proportional to the distance between the camera position
	//and the follow object position

	Vector2D dist = (getPos() - *follow->getPos()) * 0.05f;

	vel->setX(dist.getX());
	vel->setY(dist.getY());

}

void Camera::render(Entity* p, std::vector<Set*> bg, std::vector<std::vector<Set*>*>* set, std::vector<Coin*> coins, std::vector<Mushroom*> mushrooms, std::vector<Goomba*> goombas) {

	p->setPos(&(p->getPos() + this->getVel() * p->getDepth()));

	for (Entity* e : bg) {
		e->setPos(&(e->getPos() + this->getVel() * e->getDepth()));
		e->render();
	}

	p->render();

	for (Mushroom* m : mushrooms) {
		m->setPos(&(m->getPos() + this->getVel() * m->getDepth()));
		m->render();
	}

	for (Goomba* g : goombas) {
		g->setPos(&(g->getPos() + this->getVel() * g->getDepth()));
		g->render();
	}

	for (std::vector<Set*>* st : *set) {
		for (Set* s : *st) {
			s->setPos(&(s->getPos() + this->getVel() * s->getDepth()));
			s->render();
		}
	}

	for (Coin* c : coins) {
		c->setPos(&(c->getPos() + this->getVel() * c->getDepth()));
		c->render();
	}




}