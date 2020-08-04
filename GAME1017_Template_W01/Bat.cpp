#include "Bat.h"
#include "LevelManager.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Display.h"

Bat::Bat(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP) : Enemy(s, d, p, k, animationP)
{
	m_scaleRendering = 5.0;
	m_timerAtck = 0;
	updateCollisionBox(125.0f, 150.0f, 175.f,75.0f);
	m_vel.x = -2;
	TEMA::RegisterSpriteSheet("Img/Bat.txt", "Img/Bat.png", "Bat");
	m_spritesheet = TEMA::GetSpriteSheet("Bat");

	m_currentAnimation = new Animation();

	m_Arun = new Animation();
	m_Aattack = new Animation();

	buildAnimation();

	setState(EnemyState::RUN);
}

void Bat::Render()
{
	m_currentAnimation->RenderAnimation(m_dst, 0, m_scaleRendering);
}

void Bat::Update()
{
	Move(-LevelManager::velocity + m_vel.x, 0);
	m_currentAnimation->playAnimation(10);
}

void Bat::HandleEvents()
{
	auto positionPlayer = Display::Instance()->getPlayers()->getList()[0]->GetDstP();
	float distance = abs(positionPlayer->x - m_dst.x);
	switch (m_currentState)
	{
	case EnemyState::RUN:
		if (distance < 300)
			setState(EnemyState::ATTACK);
		break;
	case EnemyState::ATTACK:
		break;
	default:
		break;
	}
}

void Bat::setState(EnemyState state)
{
	m_currentState = state;
	switch (m_currentState)
	{
	case EnemyState::RUN:
		m_currentAnimation = m_Arun;
		break;
	case EnemyState::ATTACK:
		m_currentAnimation = m_Aattack;
		break;
	default:
		break;
	}

}

void Bat::buildAnimation()
{
	m_Arun->addSpriteSheet("Bat");
	m_Arun->addFrame(m_spritesheet->getFrame("flight1"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight2"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight3"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight4"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight5"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight6"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight7"));
	m_Arun->addFrame(m_spritesheet->getFrame("flight8"));


	m_Aattack->addSpriteSheet("Bat");
	m_Aattack->addFrame(m_spritesheet->getFrame("attack1"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack2"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack3"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack4"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack5"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack6"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack7"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack8"));

}
