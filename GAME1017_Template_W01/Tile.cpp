#include "Tile.h"
#include "LevelManager.h"
void Tile::Update()
{
	Move(-LevelManager::velocity, 0.0f);
}
