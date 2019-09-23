#include "textureManager.h"

std::map<const char*, SDL_Texture*> TextureManager::textures;


SDL_Texture* TextureManager::loadTexture(const char* src, SDL_Renderer* renderer) {

	if (textures.find(src) == textures.end()){

		SDL_Surface *surface = IMG_Load(src);
		std::cout << "IMG_Load: %s\n" << IMG_GetError() << std::endl;
		SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		textures.emplace(src, tex);
		return tex;
	}
	else {
		return textures[src];
	}
}