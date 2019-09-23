#pragma once
#ifndef TEXMANAGER_H_
#define TEXMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>

class TextureManager {

private:
	typedef std::map<const char*, SDL_Texture*> TexMap;
	static TexMap textures;

public:
	static SDL_Texture* loadTexture(const char* src, SDL_Renderer* renderer);
};

#endif