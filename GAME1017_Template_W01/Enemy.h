#pragma once
#include "Sprite.h"
#include <vector>
class Enemy : public Sprite {
private:
	int timer = 0;
	int respawnTimer = rand()%60+ 60;
public:
	static int m_vel;
    static int iterations;
	Enemy(SDL_Rect s, SDL_FRect d, const char* path, std::string key);
	void Update();
	void HandleEvents();
};