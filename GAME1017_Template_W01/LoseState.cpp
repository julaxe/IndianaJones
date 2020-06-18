#include "LoseState.h"
#include"Display.h"
#include "ScoreLabel.h"
#include"StateManager.h"
#include "TitleState.h"
#include <string.h>
#include "EventManager.h"


LoseState::LoseState()
{
}

void LoseState::Update()
{
	m_pScore->Update();
	m_pRestart->Update();
	if(!RestartButton::pressed)
		m_pEscape->Update();
}

void LoseState::Render()
{
	m_pGameOver->Render();
	m_pScore->Render();
	m_pRestart->Render();
	m_pEscape->Render();
}

void LoseState::Enter()
{
	m_pGameOver =  new Label("title", 200, 200, "Game Over");
	m_pScore = new ScoreLabel("alpha", 200, 300, "SCORE: ");
	m_pRestart = new RestartButton({ 898,336,67,67 }, { 300,400,67,67 }, "Img/buttons_map.png", "restart");
	m_pEscape = new EscapeButton({ 0,464,67,67 }, { 400,400,67,67 }, "Img/buttons_map.png", "escape");
}

void LoseState::Exit()
{
}

void LoseState::Resume()
{
}

void LoseState::HandleEvents()
{
	if (EVMA::KeyReleased(SDL_SCANCODE_R)) 
	{
		StateManager::ChangeState(new TitleState);
	}
}

void LoseState::CreateEnemies()
{
}

void LoseState::CheckCollision()
{
}
