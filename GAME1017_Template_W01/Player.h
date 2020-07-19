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
class Player : public AnimatedSprite {
public:
	static int m_score;
	Player(SDL_Rect s, SDL_FRect d, const char* p, std::string k, int sstart, int smax, int nf);
	void Render();
	void Update();
	void HandleEvents();
	void setState(PlayerState);
	void Move();
private:
	PlayerState m_currentState = PlayerState::IDLE;
	SDL_RendererFlip m_RendererFlip = SDL_FLIP_NONE;
	float m_scaleRendering;
	int m_jump;
	
};