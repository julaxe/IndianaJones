#include "Enemy.h"
#include "MathManager.h"
#include "EnemyLaser.h"
void Enemy::Update()
{
	
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - 20, 0.1);
	
}

void Enemy::HandleEvents(std::vector<Sprite*>& list)
{
	static int timer = 0;
	if (timer > 150) { //60 frames is 1 second
		list.push_back(new EnemyLaser({ 0,0,37,13 }, { m_dst.x,m_dst.y,37,12 }, "Img/laserRed02.png", "EnemyLaser"));
		timer = 0;
	}

	timer++;
}
