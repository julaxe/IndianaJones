#include "Display.h"
#include "DebugManager.h"
#include "CollisionManager.h"

void Display::Clear()
{
	getPlayers()->getList().clear();
	getBackground()->getList().clear();
	getEnemies()->getList().clear();
	getObstacles()->getList().clear();
	getListLabels().clear();
}

void Display::DrawDebugPlayer()
{
	for (auto p : getPlayers()->getList())
	{
		DEMA::DrawRect(p->getCollisionBox(), { 255,255,255,255 });

	}
}

void Display::DrawDebugEnemies()
{
	for (auto p : getEnemies()->getList())
	{
		DEMA::DrawRect(p->getCollisionBox(), { 255,255,255,255 });

	}
}

bool Display::checkCollisionPlayersAndEnemies()
{
	for (int i = 0; i < getPlayers()->getList().size(); i++)
	{
		for (int j = 0; j < getEnemies()->getList().size(); j++)
		{
			if (COMA::AABBCheck(getPlayers()->getList()[i]->getCollisionBox(), getEnemies()->getList()[j]->getCollisionBox()))
				return true;
		}
	}
	
	return false;
}
