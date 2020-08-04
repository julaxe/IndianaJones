#include "Goblin.h"
#include "LevelManager.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Display.h"

Goblin::Goblin(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP) : Enemy(s, d, p, k, animationP)
{
	m_scaleRendering = 3.0;
	m_timerAtck = 0;
	updateCollisionBox(60.0f, 100.0f, 60.0f, -50.0f);
	m_vel.x = -8;
	TEMA::RegisterSpriteSheet("Img/goblin.txt", "Img/goblin.png", "Goblin");
	m_spritesheet = TEMA::GetSpriteSheet("Goblin");

	m_currentAnimation = new Animation();

	m_Arun = new Animation();

	buildAnimation();

	setState(EnemyState::RUN);
}

void Goblin::Render()
{
	m_currentAnimation->RenderAnimation(m_dst, 0, m_scaleRendering);
}

void Goblin::Update()
{
	Move(-LevelManager::velocity + m_vel.x, 0);
	m_currentAnimation->playAnimation(5);
}

void Goblin::HandleEvents()
{
	auto positionPlayer = Display::Instance()->getPlayers()->getList()[0]->GetDstP();
	float distance = abs(positionPlayer->x - m_dst.x);
	switch (m_currentState)
	{
	case EnemyState::RUN:
		break;
	default:
		break;
	}
}

void Goblin::setState(EnemyState state)
{
	m_currentState = state;
	switch (m_currentState)
	{
	case EnemyState::RUN:
		m_currentAnimation = m_Arun;
		break;
	default:
		break;
	}

}

void Goblin::buildAnimation()
{
	m_Arun->addSpriteSheet("Goblin");
	m_Arun->addFrame(m_spritesheet->getFrame("run1"));
	m_Arun->addFrame(m_spritesheet->getFrame("run2"));
	m_Arun->addFrame(m_spritesheet->getFrame("run3"));
	m_Arun->addFrame(m_spritesheet->getFrame("run4"));
	m_Arun->addFrame(m_spritesheet->getFrame("run5"));
	m_Arun->addFrame(m_spritesheet->getFrame("run6"));
	m_Arun->addFrame(m_spritesheet->getFrame("run7"));
	m_Arun->addFrame(m_spritesheet->getFrame("run8"));
}
