#pragma once
#include"States.h"
#include"Label.h"
#include"Engine.h"


class LoseState : public State {
private: //private properties
	//std::vector <Sprite*> DisplayList;
	Label* m_pGameOver;
	Label* m_pScore;
public: //public methods
	LoseState();
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume();
	void HandleEvents();
	void CreateEnemies();
	void CheckCollision();
};