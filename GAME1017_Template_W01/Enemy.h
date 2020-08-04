#pragma once
#include "Sprite.h"
enum class EnemyState
{
	RUN,
	ATTACK
};
class Enemy : public AnimatedSprite {
public:
	Enemy(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP) :AnimatedSprite(s, d, p ,k, animationP)
	{}
	virtual void Render() {}
	virtual void Update() {}
	virtual void HandleEvents() {}

	virtual void setState(EnemyState) = 0;
	EnemyState getState() { return m_currentState; }
protected:
	float m_scaleRendering;
	EnemyState m_currentState;
};
