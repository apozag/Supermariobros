#include "Coin.h"

void Coin::pickup() {
	//this->clear();
}
void Coin::clear() {
	SDL_DestroyTexture(this->getTexture());
}

void Coin::render() {
	SDL_RenderCopy(getRenderer(), getTexture(), NULL, getDstRect());
}