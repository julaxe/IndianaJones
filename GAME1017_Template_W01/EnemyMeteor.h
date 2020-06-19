#pragma once
#include "Sprite.h"

class EnemyMeteor : public Sprite {
public:
	EnemyMeteor(SDL_Rect s, SDL_FRect d, const char* path, std::string key) : Sprite(s,d,path,key)
	{
		m_type = ENEMYMETEOR;
	}
	void Update();
private:

};