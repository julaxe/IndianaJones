#pragma once
#include "Button.h"
class TitleButton : public Button {
private:
public:
	TitleButton(SDL_Rect src, SDL_FRect dst, const char* path, std::string key) : Button(src, dst, path, key){}
	void Execute();

};