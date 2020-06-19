#include "EnemyMeteor.h"
#include "MathManager.h"

void EnemyMeteor::Update()
{
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - 20, 0.1);
}
