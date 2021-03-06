#pragma once
#include "Label.h"
#include "List.h"
#include "LevelManager.h"

class Display {
public:
	static Display* Instance() {
		if (m_Instance == nullptr) {
			m_Instance = new Display();
		}
		return m_Instance;
	}
	
	
	void Update()
	{
		Backgrounds->Update();
		Players->Update();
		Tiles->Update();
		Obstacles->Update();
		Enemies->Update();
	}
	void Render()
	{
		Backgrounds->Render();
		LevelManager::DrawLevel();
		Players->Render();
		Tiles->Render();
		Obstacles->Render();
		Enemies->Render();
	}
	void HandleEvents()
	{
		Backgrounds->HandleEvents();
		Players->HandleEvents();
		Tiles->HandleEvents();
		Obstacles->HandleEvents();
		Enemies->HandleEvents();
	}
	void Clear();

	List* getBackground() { return Backgrounds; }
	List* getPlayers() { return Players; }
	List* getTiles() { return Tiles; }
	List* getObstacles() { return Obstacles; }
	List* getEnemies() { return Enemies; }
	std::vector<Label*> &getListLabels() { return listLabels; }

	void DrawDebugPlayer();
	void DrawDebugEnemies();

	bool checkCollisionPlayersAndEnemies();
	bool PlayerDeath();
	


private:
	List* Backgrounds;
	List* Players;
	List* Tiles;
	List* Obstacles;
	List* Enemies;
	
	std::vector<Label*> listLabels;
	static Display* m_Instance;

	Display()
	{
		Backgrounds = new List();
		Players = new List();
		Tiles = new List();
		Obstacles = new List();
		Enemies = new List();
	}
	~Display() {}

};
