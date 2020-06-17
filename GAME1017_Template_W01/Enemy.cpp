#include "Enemy.h"
#include "MathManager.h"
#include "EnemyLaser.h"
#include "Display.h"

int Enemy::iterations = 0;
Enemy::Enemy(SDL_Rect s, SDL_FRect d, const char* path, std::string key) :Sprite(s, d, path, key) 
{
	m_type = ENEMY;
	iterations++;
	std::cout << iterations << std::endl;
}
void Enemy::Update()
{
	if (iterations >= 5) 
	{
		m_vel += 5;
		iterations = 0;
	}
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - m_vel, 0.1);
}

void Enemy::HandleEvents()
{
	
	if (timer > respawnTimer) { //60 frames is 1 second -> 10frames = 0.18 s
		respawnTimer = rand() % 60 + 60;
		Display::Instance()->getList().push_back(new EnemyLaser({ 0,0,37,13 }, { m_dst.x,m_dst.y,37,12 }, "Img/laserRed02.png", "EnemyLaser"));
		timer = 0;
	}
	
	timer++;
}
