#pragma once
#include "Sprite.h"
#include <vector>
enum Directions {
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};
class Player : public AnimatedSprite {
private:

public:
	Player(SDL_Rect s, SDL_FRect d, const char* p, std::string k, int sstart, int smax, int nf) : AnimatedSprite(s, d, p, k, sstart, smax, nf) 
	{
		m_angle = 90; m_type = PLAYER;
	}
	void Update();
	void HandleEvents(std::vector<Sprite*>& list);
	void setMovement(Directions);
	void Move();
};