#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"
#include <iostream>

enum ObjectType {
	NONE = 0,
	PLAYER,
	PLAYERLASER,
	ENEMY,
	ENEMYLASER,
	BACKGROUND,
	BUTTON,
	ANIMATION
};
class Sprite // Inline class.
{
public: // Inherited and public.
	Sprite(SDL_Rect s, SDL_FRect d, const char* path, std::string key);
	void Render();
	virtual void Update();
	virtual void HandleEvents();
	SDL_Rect* GetSrcP() { return &m_src; }
	SDL_FRect* GetDstP() { return &m_dst; }
	void SetPosition(float x, float y) { m_dst.x = x - m_dst.w / 2; m_dst.y = y - m_dst.h / 2; }
	double& GetAngle() { return m_angle; }
	void SetAngle(double a) { m_angle = a; }
	ObjectType GetType() { return m_type; }
	void setBoundaries(SDL_Rect b);
	bool checkBoundaries();
protected: // Private BUT inherited.
	double m_angle;
	SDL_Rect m_src;
	SDL_FRect m_dst;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
	const char* m_path;
	std::string m_key;
	ObjectType m_type;
private: // Private NOT inherited.
};

class AnimatedSprite : public Sprite// Also inline.
{
public:
	AnimatedSprite(SDL_Rect s, SDL_FRect d, const char* p, std::string k, int sstart, int smax, int nf)
		:Sprite(s, d, p, k), m_sprite(sstart), m_spriteMax(smax), m_frameMax(nf) {}
	void Animate()
	{

		m_frame++;
		if (m_frame == m_frameMax)
		{
			m_frame = 0;
			if (++m_sprite == m_spriteMax) {
				m_sprite = 0;
				m_animationDone = true;
			}
		}
		m_src.x = m_src.w * m_sprite;
	}
	virtual void Update();
	virtual void HandleEvents();
	bool AnimationDone() { return m_animationDone; }
protected:
	int m_sprite,		// The current sprite index in row.
		m_spriteMax,	// The sprite index to end animation on.
		m_frame = 0,	// Frame counter.
		m_frameMax;		// Number of frames to display each sprite.
	bool m_animationDone = false;
};

/* Note: A lot of animation methods use a modulus operation to wrap the frames
   around, but I am not. I may have different cycles on the same row and so I
   want total control over my animations without having it look too complex. */

#endif