#include "Background.h"
#include "Engine.h"

void Background::Update()
{
	m_dst.x -= m_velocity;
	if (m_dst.x < -WIDTH * 1.25) {
		m_dst.x = WIDTH * 1.25;
	}
}
