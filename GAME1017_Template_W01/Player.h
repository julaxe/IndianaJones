#pragma once
#include "Sprite.h"
#include <vector>

enum class PlayerState {
	IDLE,
	RUN,
	JUMP,
	SLIDE,
	DIE
};
enum class JumpingState {
	PREPARING,
	RISING,
	FLOATING,
	FALLING
};
class Player : public AnimatedSprite {
public:
	static int m_score;
	Player(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP);
	void Render();
	void Update();
	void HandleEvents();
	void setState(PlayerState);
	void setJumpingState(JumpingState);
private:
	PlayerState m_currentState;
	JumpingState m_currentJumpingState;
	SDL_RendererFlip m_RendererFlip = SDL_FLIP_NONE;
	float m_scaleRendering;
	int m_jumpISpeed, m_maxVelX, m_maxVelY, m_runningISpeed;

	
};