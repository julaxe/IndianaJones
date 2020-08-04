#include "Animation.h"
#include "TextureManager.h"
#include "Engine.h"
Animation::Animation() 
{
	m_currentFrame = 0;
	m_timerAnimation = 0;
	m_animationDone = false;
}
bool Animation::animationDone()
{
	return m_animationDone;
}
void Animation::RenderAnimation(SDL_FRect dst, float angle, int scale)
{
	if (listFrames.size() > 0)
	{
		auto Texture = TextureManager::GetTexture(m_spriteSheetName);
		auto Renderer = Engine::Instance().GetRenderer();
		auto src = listFrames[m_currentFrame]->getSrc();
		dst.w = src->w * scale;
		dst.h = src->h * scale;
		SDL_RenderCopyExF(Renderer, Texture, src, &dst, angle, 0, SDL_FLIP_HORIZONTAL);
	}
}
void Animation::playAnimation(int velocity)
{
	
	m_animationDone = false;
	
	if (m_timerAnimation >= velocity)
	{
		m_timerAnimation = 0;
		m_currentFrame++;
		if (m_currentFrame >= listFrames.size())
		{
			m_currentFrame = 0;
			m_animationDone = true;
		}
	}
	m_timerAnimation++;
}
