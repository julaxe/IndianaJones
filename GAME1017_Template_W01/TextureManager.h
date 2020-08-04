#pragma once
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "SpriteSheet.h"

class TextureManager
{
public: // Public methods.
	static void Init();
	static void RegisterTexture(const char* path, const std::string key);
	static SDL_Texture* GetTexture(const std::string key);
	static void RegisterSpriteSheet(std::string text, const char* path, const std::string key);
	static SpriteSheet* GetSpriteSheet(const std::string key);
	static void Quit();
private: // Private properties.
	static std::map<std::string, SDL_Texture*> s_textures;
	static std::map<std::string, SpriteSheet*> s_spriteSheets;
private: // Private methods.
	TextureManager();
};

typedef TextureManager TEMA;

#endif