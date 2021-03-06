#pragma once
#include "Tile.h"
#include <vector>
class LevelManager {
public:
	static void GenerateTiles();
	static void DrawLevel();
	static void DrawCollisionBoxes();
	static void UpdateLevel();
	static void GenerateNewCol();
	static void GenerateNewEnemies();
	static void Clear();
	
	static int m_TileSize;
	static std::vector<std::vector<Tile*>> m_level;
	static float velocity;
	static int spawningTimer;
	static int timer;

private:
	static bool deleteColumnsReadyOutOfScreen();
	static bool deleteEnemiesReadyOutOfScreen();
};