#include "Sprite.h"
#include "Engine.h"
#include "TextureManager.h"

Sprite::Sprite(SDL_Rect s, SDL_FRect d, const char* path, std::string key) {
	m_src = s; 
	m_dst = d; 
	m_path = path; 
	m_key = key;
	m_angle = 0.0;
	m_dst.x = d.x - m_dst.w / 2;
	m_dst.y = d.y - m_dst.h / 2;
	m_pRend = Engine::Instance().GetRenderer();
	TEMA::RegisterTexture(m_path, m_key);
	m_pText = TEMA::GetTexture(m_key);
}
void Sprite::Render() { 
	SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE); 
}

void Sprite::Update()
{
}

void Sprite::HandleEvents()
{
}

void Sprite::setBoundaries(SDL_Rect b)
{
	if (m_dst.x < b.x+10) {
		m_dst.x = b.x+10 ;
		m_acc.x = 0;
	}
	if (m_dst.x > b.x + b.w - m_dst.w) {
		m_dst.x = b.x + b.w - m_dst.w;
		m_acc.x = 0;
	}
	if (m_dst.y < b.y) {
		m_dst.y = b.y;
	}
	if (m_dst.y > b.y + b.h - m_dst.h) {
		m_dst.y = b.y + b.h - m_dst.h;
	}
	
}

bool Sprite::checkBoundaries()
{
	if (m_dst.x < -WIDTH * 2)return true;
	else if (m_dst.x > WIDTH * 2) return true;
	else return false;
}

void Sprite::setAlpha(SDL_Texture*s, int a)
{
	SDL_SetTextureAlphaMod(s, a);
}

void AnimatedSprite::Render() {}

void AnimatedSprite::Update() {}

void AnimatedSprite::HandleEvents() {}
