#include "Set.h"

void Set::update(const double &dt) {

}
void Set::render() {
	SDL_RenderCopy(getRenderer(), getTexture(), NULL, getDstRect());
}
void Set::clear() {

}