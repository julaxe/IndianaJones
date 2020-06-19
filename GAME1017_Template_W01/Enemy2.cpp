#include "Enemy2.h"
#include "Enemy.h"
#include "MathManager.h"
#include "Display.h"
#include "EnemyLaser.h"

void Enemy2::Update()
{
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - Enemy::m_vel, 0.1);
	if (m_dst.x < 750 && m_dst.x > 400) {
		for (auto p : Display::Instance()->getList()) {
			if (p->GetType() == PLAYER) {
				m_dst.y = MAMA::LerpD(m_dst.y, p->GetDstP()->y, 0.05);
			}
		}
	}

	if (timer > respawnTimer) { //60 frames is 1 second -> 10frames = 0.18 s
		respawnTimer = rand() % 30 + 45;
		Display::Instance()->getList().push_back(new EnemyLaser({ 0,0,37,13 }, { m_dst.x,m_dst.y,37,12 }, "Img/laserRed02.png", "EnemyLaser"));
		timer = 0;
	}

	timer++;
	
}
