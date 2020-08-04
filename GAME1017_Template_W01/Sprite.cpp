#include "Sprite.h"
#include "Engine.h"
#include "TextureManager.h"

Sprite::Sprite(SDL_Rect s, SDL_FRect d, const char* path, std::string key) {
	m_src = s; 
	m_dst = d; 
	m_path = path; 
	m_key = key;
	m_angle = 0.0;
	m_vel = { 0,0 };
	m_acc = { 0,0 };
	m_centerPoint.x = d.x;
	m_centerPoint.y = d.y;
	m_dst.x = d.x - m_dst.w / 2;
	m_dst.y = d.y - m_dst.h / 2;
	m_pRend = Engine::Instance().GetRenderer();
	if (m_path != "")
	{
		TEMA::RegisterTexture(m_path, m_key);
	}
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

bool Sprite::checkBoundaries(SDL_Rect b)
{
	if (m_collisionBox.x < b.x+10 
	|| m_collisionBox.x > b.x + b.w - m_collisionBox.w
	|| m_collisionBox.y < b.y
	|| m_collisionBox.y > b.y + b.h - m_collisionBox.h) 
	{
		
		return true;
	}
	
	return false;
}

void Sprite::setAlpha(SDL_Texture*s, int a)
{
	SDL_SetTextureAlphaMod(s, a);
}

void Sprite::updateCollisionBox(float w, float h)
{
	m_collisionBox = { m_centerPoint.x - w * 0.5f, m_centerPoint.y - h * 0.5f,w,h };
}

void Sprite::Move(float velX, float velY)
{
	m_dst.x += velX;
	m_dst.y += velY;
	m_collisionBox.x += velX;
	m_collisionBox.y += velY;
	m_centerPoint = { m_dst.x + m_dst.w*0.5f, m_dst.y + m_dst.h * 0.5f};
}

void AnimatedSprite::Render() {}

void AnimatedSprite::Update() {}

void AnimatedSprite::HandleEvents() {}
