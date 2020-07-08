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

	static bool m_pause;
private: //private methods
};
