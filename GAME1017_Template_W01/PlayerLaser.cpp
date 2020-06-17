#include "PlayerLaser.h"
#include "MathManager.h"

void PlayerLaser::Update()
{
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x + 100, 0.1);
}
