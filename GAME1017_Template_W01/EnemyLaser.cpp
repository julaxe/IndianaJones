#include "EnemyLaser.h"
#include "MathManager.h"
#include "Enemy.h"

void EnemyLaser::Update()
{
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - 20 - Enemy::m_vel, 0.1);
}
