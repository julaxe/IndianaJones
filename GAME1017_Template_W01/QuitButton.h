#pragma once
#include "Button.h"
class QuitButton : public Button {
private:
public:
	static bool pressed;
	QuitButton(SDL_Rect src, SDL_FRect dst, const char* path, std::string key) : Button(src, dst, path, key) {}
	void Execute();
};