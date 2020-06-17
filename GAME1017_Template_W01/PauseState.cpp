#include "PauseState.h"

PauseState::PauseState()
{
}

void PauseState::Update()
{
}

void PauseState::Render()
{
	m_pPauseLabel->Render();
}

void PauseState::Enter()
{
	m_pPauseLabel = new Label("title", 400, 300, "PAUSE");
}

void PauseState::Exit()
{
}

void PauseState::Resume()
{
}

void PauseState::HandleEvents()
{
}
