#pragma once
#include "States.h"
#include "Label.h"

class PauseState : public State {
private: //private properties
	Sprite* m_pBackground;
	Label* m_pPauseLabel;

public: //public methods
	PauseState();
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume();
	void HandleEvents();

private: //private methods
	
};