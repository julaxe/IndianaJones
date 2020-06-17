#pragma once
#include "States.h"
#include "TitleButton.h"
#include <vector>

class PlayState : public State {
private: //private properties
	//std::vector <Sprite*> DisplayList;

public: //public methods
	PlayState();
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume();
	void HandleEvents();
	void CreateEnemies();
	void CheckCollision();

private: //private methods
};
