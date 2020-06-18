#pragma once
#include"States.h"
#include"Label.h"
#include"RestartButton.h"
#include "EscapeButton.h"


class LoseState : public State {
private: //private properties
	//std::vector <Sprite*> DisplayList;
	Label* m_pGameOver;
	Label* m_pScore;
	RestartButton* m_pRestart;
	EscapeButton* m_pEscape;
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