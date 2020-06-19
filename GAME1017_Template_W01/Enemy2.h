#pragma once
#include "Sprite.h"

class Enemy2 : public Sprite {
public:
	Enemy2(SDL_Rect s, SDL_FRect d, const char* path, std::string key) : Sprite(s, d, path, key)
	{
		m_type = ENEMY2;
	}
	void Update();
private:
	int timer = 0;
	int respawnTimer = rand() % 30 + 20;

};