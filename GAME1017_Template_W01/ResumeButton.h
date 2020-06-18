#pragma once
#include "Button.h"
class ResumeButton : public Button {
private:
public:
	ResumeButton(SDL_Rect src, SDL_FRect dst, const char* path, std::string key) : Button(src, dst, path, key) {}
	void Execute();

};