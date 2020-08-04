#pragma once
#include "Label.h"
#include "List.h"
#include "LevelManager.h"
#include "DebugManager.h"

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

	List* getBackground() { return Backgrounds; }
	List* getPlayers() { return Players; }
	List* getTiles() { return Tiles; }
	List* getObstacles() { return Obstacles; }
	List* getEnemies() { return Enemies; }
	std::vector<Label*> &getListLabels() { return listLabels; }

	void DrawDebugPlayer()
	{
		for (auto p : getPlayers()->getList())
		{
			DEMA::DrawRect(p->getCollisionBox(), { 255,255,255,255 });

		}
	}
	void DrawDebugEnemies()
	{
		for (auto p : getEnemies()->getList())
		{
			DEMA::DrawRect(p->getCollisionBox(), { 255,255,255,255 });

		}
	}

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
