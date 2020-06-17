#pragma once
#include "Sprite.h"
#include <vector>
class Enemy : public Sprite {
public:
	Enemy(SDL_Rect s, SDL_FRect d, const char* path, std::string key) :Sprite(s,d,path,key) 
	{
		m_type = ENEMY;
	}
	void Update();
	void HandleEvents(std::vector<Sprite*>& list);
};