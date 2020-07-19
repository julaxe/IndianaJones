#include "LevelManager.h"
#include "Engine.h"
#include "DebugManager.h"
int LevelManager::m_TileSize = 128;
std::vector<std::vector<Tile*>> LevelManager::m_level;
void LevelManager::GenerateTiles()
{
	for (int x = 0; x*m_TileSize < WIDTH*1.5; x++)
	{
		std::vector<Tile*> col;
		for (int y = 0; y* m_TileSize < HEIGHT*1.5; y++)
		{
			float posX = x * m_TileSize;
			float posY = y * m_TileSize;
			if (posY < 500)
			{
				col.push_back(nullptr);
			}
			else
			{
				col.push_back(new Tile({ 0,0,128,128 }, { posX,posY,(float) m_TileSize,(float)m_TileSize }, "Img/Tile/5.png","Tile"));
			}
		}
		m_level.push_back(col);
	}
}

void LevelManager::DrawLevel()
{
	for (auto col : m_level)
	{
		for (auto tile : col)
		{
			if(tile != nullptr)
				tile->Render();
		}
	}
}
void LevelManager::DrawCollisionBoxes()
{
	for (auto col : m_level)
	{
		for (auto tile : col)
		{
			if (tile != nullptr)
				DEMA::DrawRect(tile->getCollisionBox(), { 255,255,255,255 });
		}
	}
}
