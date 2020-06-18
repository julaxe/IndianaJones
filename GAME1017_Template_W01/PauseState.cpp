#include "PauseState.h"
#include "TextureManager.h"
#include "StateManager.h"
#include"LoseState.h"

PauseState::PauseState()
{
}

void PauseState::Update()
{
	m_pResumeButton->Update();
	m_pQuitButton->Update();
}

void PauseState::Render()
{
	m_pPauseLabel->Render();
	m_pPause->Render();
	m_pResumeButton->Render();
	m_pQuitButton->Render();
}

void PauseState::Enter()
{
	m_pPauseLabel = new Label("title", 250,250,"PAUSE");
	m_pPause = new Sprite({ 0,0,800,900 }, { 400,350,900,1000 }, "Img/pause.png", "pause");
	SDL_SetTextureAlphaMod(TextureManager::GetTexture("pause"), 90);
	m_pResumeButton = new ResumeButton({ 0,272,66,66 }, { 350,400,66,66 }, "Img/buttons_map.png", "resume");
	m_pQuitButton = new QuitButton({ 0,404,66,66 }, { 450,400,66,66 }, "Img/buttons_map.png", "quit");
}

void PauseState::Exit()
{
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