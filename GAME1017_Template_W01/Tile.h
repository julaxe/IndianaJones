#pragma once
#include "Sprite.h"
class Tile : public Sprite {
public:
	Tile(SDL_Rect s, SDL_FRect d, const char* p, std::string k) : Sprite(s, d, p, k)
	{
		m_collisionBox = { m_dst.x, m_dst.y, m_dst.w, m_dst.h };
	}
	void Update() override;
private:
	

};