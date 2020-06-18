#include "LoseState.h"
#include"Display.h"
#include "ScoreLabel.h"
#include"StateManager.h"
#include "TitleState.h"
#include <string.h>

LoseState::LoseState()
{
}

void LoseState::Update()
{
}

void LoseState::Render()
{
	for (auto d : Display::Instance()->getListEnd()) {
		d->Render();
	}
}

void LoseState::Enter()
{
	Display::Instance()->getListEnd().push_back(new Label("title", 250, 250, "Game Over"));
	Display::Instance()->getListEnd().push_back(new ScoreLabel("alpha", 10, 10, "SCORE: "));
}

void LoseState::Exit()
{
}

void LoseState::Resume()
{
}

void LoseState::HandleEvents()
{
	if (SDL_SCANCODE_R) 
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
