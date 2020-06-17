#include "BackgroundPlayScene.h"
#include "Engine.h"

void BackgroundPlayScene::Update()
{
	m_dst.x--;
	if (m_dst.x < -WIDTH * 1.25) {
		m_dst.x = WIDTH * 1.25;
	}
}
