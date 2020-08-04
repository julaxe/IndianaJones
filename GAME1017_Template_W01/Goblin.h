#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "SpriteSheet.h"
class Goblin : public Enemy {
public:
	Goblin(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP);
	virtual void Render();
	virtual void Update();
	virtual void HandleEvents();

	void setState(EnemyState state) override;
private:
	void buildAnimation();
	SpriteSheet* m_spritesheet;
	Animation* m_currentAnimation;

	int m_timerAtck;
	Animation* m_Arun;
};
