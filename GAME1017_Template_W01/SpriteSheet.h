#pragma once
#include "Frame.h"
#include <map>
class SpriteSheet {
public:
	SpriteSheet(std::string text, const char* path, std::string key);
	void loadText();
	std::map<std::string, Frame*>& getFrames() { return framesOnSpriteSheet; }
	Frame* getFrame(std::string name) { return framesOnSpriteSheet[name]; }
private:
	void addFrame(Frame*);
	const char* path;
	std::string text;
	std::string key;
	std::map<std::string,Frame*> framesOnSpriteSheet;
};