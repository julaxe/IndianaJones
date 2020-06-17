#pragma once
#include "Label.h"
class ScoreLabel : public Label {
public:
	ScoreLabel(std::string key, const float x, const float y, const char* str, const SDL_Color col = { 255,255,255,255 }) : Label(key, x,y,str,col)
	{
		
	}
	void Update();
};
