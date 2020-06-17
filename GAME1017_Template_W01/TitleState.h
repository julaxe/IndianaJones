#pragma once
#include "States.h"
#include "TitleButton.h"
#include "Label.h"

class TitleState : public State {
private: //private properties
	Sprite* m_pBackground;
	TitleButton* m_pStartGameButton;
	Label* m_pTitle;
	
public: //public methods
	TitleState();
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume();
	void HandleEvents();

private: //private methods
};
