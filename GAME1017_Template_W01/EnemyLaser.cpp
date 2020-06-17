#include "EnemyLaser.h"
#include "MathManager.h"

void EnemyLaser::Update()
{
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - 40, 0.1);
}
