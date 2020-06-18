#pragma once
#include "Button.h"
class RestartButton : public Button {
private:
public:
	static bool pressed;
	RestartButton(SDL_Rect src, SDL_FRect dst, const char* path, std::string key) : Button(src, dst, path, key) { pressed = false; }
	void Execute();
};