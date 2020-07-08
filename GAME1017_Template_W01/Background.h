#pragma once
#include "Sprite.h"
class Background : public Sprite {
public:
	Background(SDL_Rect s, SDL_FRect d, const char* p, std::string k, int velocity) : Sprite(s, d, p, k) 
	{
		m_velocity = velocity;
	}
	void Update();
private:
	int m_velocity = 0;
};
