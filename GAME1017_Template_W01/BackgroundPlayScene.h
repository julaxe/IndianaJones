#pragma once
#include "Sprite.h"
class BackgroundPlayScene : public Sprite {
private:

public:
	BackgroundPlayScene(SDL_Rect s, SDL_FRect d, const char* p, std::string k) : Sprite(s, d, p, k) {}
	void Update();
};
