#pragma once
#include "Sprite.h"
class PlayerLaser : public Sprite {
public:
	PlayerLaser(SDL_Rect s, SDL_FRect d, const char* path, std::string key) :Sprite(s, d, path, key)
	{
		m_dst.x = d.x + 45; m_dst.y = d.y + 20; m_type = PLAYERLASER; /*the player sprite is 40*57 */
	}
	void Update();
};