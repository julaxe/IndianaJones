#include "TitleState.h"
#include "Engine.h"
#include "EventManager.h"

TitleState::TitleState()
{
	Enter();
}

void TitleState::Update()
{
	m_pStartGameButton->Update();
}

void TitleState::Render()
{
	m_pBackground->Render();
	m_pStartGameButton->Render();
}

void TitleState::Enter()
{
	m_pBackground = new Sprite({ 0,0,200,100 }, {WIDTH/2,HEIGHT/2,200,100}, "Img/circle.png", "circles");
	m_pStartGameButton = new TitleButton({0,0,400,100 }, { WIDTH / 2,2 * HEIGHT / 3,400,100 }, "Img/play.png", "play");
}

void TitleState::Exit()
{
}

void TitleState::Resume()
{
}

void TitleState::HandleEvents()
{
	
}
