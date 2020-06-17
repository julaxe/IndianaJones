#pragma once
#include "Sprite.h"
class EnemyLaser : public Sprite {
public:
	EnemyLaser(SDL_Rect s, SDL_FRect d, const char* path, std::string key) :Sprite(s, d, path, key)
	{
		m_dst.x = d.x - 45; m_dst.y = d.y + 20; m_type = ENEMYLASER; /*the player sprite is 40*57 */
	}
	void Update();
};