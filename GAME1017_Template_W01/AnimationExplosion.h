#pragma once
#include "Sprite.h"
class AnimationExplosion : public AnimatedSprite {
public:
	AnimationExplosion(SDL_Rect s, SDL_FRect d, const char* p, std::string k, int sstart, int smax, int nf)
		:AnimatedSprite(s, d, p, k, sstart, smax, nf) 
	{
		m_type = ANIMATION;
	}
	void Update()
	{
		Animate();
		if (AnimationDone())
		{
			m_frame = 0;
		}
	}
};