#include "LevelManager.h"
#include "Engine.h"
#include "DebugManager.h"
int LevelManager::m_TileSize = 128;
std::vector<std::vector<Tile*>> LevelManager::m_level;
void LevelManager::GenerateTiles()
{
	for (int x = 0; x*m_TileSize < (15* m_TileSize); x++)
	{
		std::vector<Tile*> col;
		for (int y = 0; y* m_TileSize < (8 * m_TileSize); y++)
		{
			float posX = x * m_TileSize;
			float posY = y * m_TileSize;
			if (posY < 5 * m_TileSize)
			{
				col.push_back(nullptr);
			}
			else if (posY == 5 * m_TileSize)
			{
				col.push_back(new Tile({ 0,0,128,128 }, { posX,posY,(float)m_TileSize,(float)m_TileSize }, "Img/Tile/2.png", "Tile"));
			}
			else
			{
				col.push_back(new Tile({ 0,0,128,128 }, { posX,posY,(float)m_TileSize,(float)m_TileSize }, "Img/Tile/5.png", "Tile2"));
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

void LevelManager::UpdateLevel()
{
	for (auto col : m_level)
	{
		for (auto tile : col)
		{
			if(tile != nullptr)
				tile->Update();
		}
	}
	if (deleteColumnsReadyOutOfScreen())
	{
		GenerateNewCol();
	}


}

void LevelManager::GenerateNewCol()
{
	std::vector<Tile*> col;
	for (int y = 0; y * m_TileSize < 8 * m_TileSize; y++)
	{
		float posX = 13 * m_TileSize;
		float posY = y * m_TileSize;
		if (posY < 5 * m_TileSize)
		{
			col.push_back(nullptr);
		}
		else if (posY == 5 * m_TileSize)
		{
			col.push_back(new Tile({ 0,0,128,128 }, { posX,posY,(float)m_TileSize,(float)m_TileSize }, "Img/Tile/2.png", "Tile"));
		}
		else
		{
			col.push_back(new Tile({ 0,0,128,128 }, { posX,posY,(float)m_TileSize,(float)m_TileSize }, "Img/Tile/5.png", "Tile2"));
		}
	}
	m_level.push_back(col);
}

bool LevelManager::deleteColumnsReadyOutOfScreen()
{
	for (int tile = 0; tile < m_level[0].size(); tile++)
	{
		if (m_level[0][tile])
		{
			if (m_level[0][tile] != nullptr)
			{
				if (m_level[0][tile]->GetDstP()->x < -2 * m_TileSize)
				{
					m_level.erase(m_level.begin());
					return true;
				}
			}
		}
	}
	return false;
	
}


