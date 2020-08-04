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
	ENEMYMETEOR,
	ENEMY2,
	BACKGROUND,
	BUTTON,
	ANIMATION
};
class Sprite // Inline class.
{
public: // Inherited and public.
	Sprite(SDL_Rect s, SDL_FRect d, const char* path, std::string key);
	virtual void Render();
	virtual void Update();
	virtual void HandleEvents();
	SDL_Rect* GetSrcP() { return &m_src; }
	SDL_FRect* GetDstP() { return &m_dst; }
	SDL_FRect& GetVelocity() { return m_vel; }
	SDL_FRect& GetAceleration() { return m_acc; }
	void SetPosition(float x, float y) { m_dst.x = x - m_dst.w / 2; m_dst.y = y - m_dst.h / 2; }
	double& GetAngle() { return m_angle; }
	void SetAngle(double a) { m_angle = a; }
	ObjectType GetType() { return m_type; }
	bool checkBoundaries(SDL_Rect b);
	void setAlpha(SDL_Texture*s, int a);
	SDL_FRect& getCollisionBox() { return m_collisionBox; }
	void updateCollisionBox(float w, float h);
	void Move(float velX, float velY);

protected: // Private BUT inherited.
	double m_angle;
	SDL_Rect m_src;
	SDL_FRect m_dst;
	SDL_FRect m_vel;
	SDL_FRect m_acc;
	SDL_FPoint m_centerPoint;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
	const char* m_path;
	std::string m_key;
	ObjectType m_type;
	SDL_FRect m_collisionBox;
	float m_gravity = 0.5f;
	float m_friction = 1.0f;
private: // Private NOT inherited.
};

struct AnimationParameters {
	AnimationParameters(int sstart /*sstart*/, int smax /*smax*/, int nf /*nf*/, int nRows /*nRows*/, int nColumns /*nColumns*/,int initialY)
	{
		this->sstart = sstart;
		this->smax = smax;
		this->nf = nf;
		this->nRows = nRows;
		this->nColumns = nColumns;
		this->initialY = initialY;
	}
	int sstart =0,
		smax = 0,
		nf = 0,
		nRows = 0,
		nColumns = 0,
		frameMax = 0,
		initialY = 0;
};
class AnimatedSprite : public Sprite// Also inline.
{
public:
	AnimatedSprite(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP)
		:Sprite(s, d, p, k)
	{
		m_params = new AnimationParameters(animationP.sstart, animationP.smax,
			animationP.nf, animationP.nRows,
			animationP.nColumns, animationP.initialY);
	}
	~AnimatedSprite()
	{
		delete m_params;
		m_params = nullptr;
	}
	void Animate()
	{
		m_animationDone = false;
		m_frame++;
		m_src.x = m_initialX + (m_src.w * m_sprite);
		m_src.y = m_params->initialY + (m_currentRow * m_src.h);

		if (m_frame == m_params->nf)
		{
			m_frame = 0;
			m_sprite++;
			
			if (m_currentRow < m_params->nRows && m_sprite > m_params->nColumns) //Go to the next row if not Done
			{
				m_currentRow++;
				m_sprite = 0;
			}
			if (m_currentRow == m_params->nRows && m_sprite >= m_params->smax) //reset animation if done
			{
				m_animationDone = true;
				if (m_sprite > m_params->smax)
				{
					m_sprite = m_params->sstart;
					m_currentRow = 0;
					m_animationDone = false;
				}
			}

			
		}
	}
	virtual void Update();
	virtual void HandleEvents();
	virtual void Render();
	bool AnimationDone() { return m_animationDone; }
protected:
	int m_sprite,		// The current sprite index in row.
		m_frame = 0,	// Frame counter.
		m_currentRow = 0,
		m_initialX;
	AnimationParameters* m_params;
		
	bool m_animationDone = false;
};

/* Note: A lot of animation methods use a modulus operation to wrap the frames
   around, but I am not. I may have different cycles on the same row and so I
   want total control over my animations without having it look too complex. */

#endif