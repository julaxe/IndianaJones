#include "Skeleton.h"
#include "LevelManager.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Display.h"

Skeleton::Skeleton(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP) : Enemy(s,d,p,k,animationP)
{
	m_scaleRendering = 6.0f;
	updateCollisionBox(150.0f, 250.0f, -112.0f, -170.0f);
	m_vel.x = 0;
	TEMA::RegisterSpriteSheet("Img/skeletonSheet.txt", "Img/skeletonSheet.png", "skeletonSheet");
	m_spritesheet = TEMA::GetSpriteSheet("skeletonSheet");


	m_Arun = new Animation();
	m_Aattack = new Animation();
	m_currentAnimation = new Animation();

	buildAnimation();

	setState(EnemyState::RUN);
}

void Skeleton::Render()
{
	m_currentAnimation->RenderAnimation(m_dst, 0, m_scaleRendering);
}

void Skeleton::Update()
{
	Move(-LevelManager::velocity + m_vel.x, 0);
	m_currentAnimation->playAnimation(10);
}

void Skeleton::HandleEvents()
{
	auto positionPlayer = Display::Instance()->getPlayers()->getList()[0]->GetDstP();
	float distance = abs(positionPlayer->x - m_dst.x);
	switch (m_currentState)
	{
	case EnemyState::RUN:
		m_vel.x = -1;
		if(distance < 500)
			setState(EnemyState::ATTACK);
		break;
	case EnemyState::ATTACK:
		m_vel.x = 0;
		break;
	default:
		break;
	}
}

void Skeleton::setState(EnemyState state)
{
	m_currentState = state;
	switch (m_currentState)
	{
	case EnemyState::RUN:
		m_currentAnimation = m_Arun;
		break;
	case EnemyState::ATTACK:
		m_dst.x -= 90;
		m_dst.y -= 25;
		m_currentAnimation = m_Aattack;
		break;
	default:
		break;
	}
	
}

void Skeleton::buildAnimation()
{
	m_Arun->addSpriteSheet("skeletonSheet");
	m_Arun->addFrame(m_spritesheet->getFrame("run1"));
	m_Arun->addFrame(m_spritesheet->getFrame("run2"));
	m_Arun->addFrame(m_spritesheet->getFrame("run3"));
	m_Arun->addFrame(m_spritesheet->getFrame("run4"));
	m_Arun->addFrame(m_spritesheet->getFrame("run5"));
	m_Arun->addFrame(m_spritesheet->getFrame("run6"));
	m_Arun->addFrame(m_spritesheet->getFrame("run7"));
	m_Arun->addFrame(m_spritesheet->getFrame("run8"));
	m_Arun->addFrame(m_spritesheet->getFrame("run9"));
	m_Arun->addFrame(m_spritesheet->getFrame("run10"));
	m_Arun->addFrame(m_spritesheet->getFrame("run11"));
	m_Arun->addFrame(m_spritesheet->getFrame("run12"));
	m_Arun->addFrame(m_spritesheet->getFrame("run13"));

	m_Aattack->addSpriteSheet("skeletonSheet");
	m_Aattack->addFrame(m_spritesheet->getFrame("attack1"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack2"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack3"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack4"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack5"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack6"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack7"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack8"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack9"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack10"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack11"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack12"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack13"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack14"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack15"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack16"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack17"));
	m_Aattack->addFrame(m_spritesheet->getFrame("attack18"));
}
