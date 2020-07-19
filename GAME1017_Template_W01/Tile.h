#pragma once
#include "Sprite.h"
class Tile : public Sprite {
public:
	Tile(SDL_Rect s, SDL_FRect d, const char* p, std::string k) : Sprite(s, d, p, k)
	{
		m_collisionBox = { (int)m_dst.x, (int)m_dst.y,(int)m_dst.w,(int)m_dst.h };
	}
private:
	

};