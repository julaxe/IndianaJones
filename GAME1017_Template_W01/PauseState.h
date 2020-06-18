#pragma once
#include "States.h"
#include "Label.h"
#include "ResumeButton.h"
#include "QuitButton.h"

class PauseState : public State {
private: //private properties
	Sprite* m_pPause;
	Label* m_pPauseLabel;
	ResumeButton* m_pResumeButton;
	QuitButton* m_pQuitButton;
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