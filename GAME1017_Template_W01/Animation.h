#pragma once
#include <vector>
#include "Frame.h"
class Animation {
public:
	Animation();
	void addFrame(Frame* frame)
	{
		listFrames.push_back(frame);
	}
	void addSpriteSheet(std::string spriteSheet)
	{
		m_spriteSheetName = spriteSheet;
	}
	bool animationDone();
	void playAnimation(int velocity);
	void RenderAnimation(SDL_FRect dst, float angle, int scale);
private:
	std::vector<Frame*> listFrames;
	std::string m_spriteSheetName;
	bool m_animationDone;
	int m_timerAnimation;
	int m_currentFrame;
};