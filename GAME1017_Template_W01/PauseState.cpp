#include "PauseState.h"
#include "TextureManager.h"
#include "StateManager.h"
#include"LoseState.h"

PauseState::PauseState()
{
}

void PauseState::Update()
{
	try {
		m_pQuitButton->Update();
		if (!QuitButton::pressed)
		{
			m_pRestartButton->Update();
			if(!RestartButton::pressed)
			m_pResumeButton->Update();
		}
		throw "";
	}
	catch(...){
		
	}
}

void PauseState::Render()
{
	m_pPauseLabel->Render();
	m_pPause->Render();
	m_pQuitButton->Render();
	m_pResumeButton->Render();
	m_pRestartButton->Render();
}

void PauseState::Enter()
{
	m_pPauseLabel = new Label("title", 250,250,"PAUSE");
	m_pPause = new Sprite({ 0,0,800,900 }, { 400,350,900,1000 }, "Img/pause.png", "pause");
	SDL_SetTextureAlphaMod(TextureManager::GetTexture("pause"), 90);
	m_pResumeButton = new ResumeButton({ 0,272,66,60 }, { 300,400,66,60 }, "Img/buttons_map.png", "resume");
	m_pQuitButton = new QuitButton({ 0,404,66,60 }, { 500,400,66,60 }, "Img/buttons_map.png", "quit");
	m_pRestartButton = new RestartButton({ 898,336,67,63 }, { 400,400,67,63 }, "Img/buttons_map.png", "quit");
}

void PauseState::Exit()
{
	delete m_pPauseLabel;
	delete m_pPause;
	delete m_pResumeButton;
	delete m_pQuitButton;
	delete m_pRestartButton;
	m_pPauseLabel = nullptr;
	m_pPause = nullptr;
	m_pResumeButton = nullptr;
	m_pQuitButton = nullptr;
	m_pRestartButton = nullptr;


}

void PauseState::Resume()
{
}

void PauseState::HandleEvents()
{
	//Bugs everything
	/*if (SDL_SCANCODE_Q)
	{
		StateManager::ChangeState(new LoseState);
	}*/ 
}