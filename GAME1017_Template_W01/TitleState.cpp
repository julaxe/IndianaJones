#include "TitleState.h"
#include "Engine.h"
#include "EventManager.h"
#include "FontManager.h"


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
	m_pTitle->Render();
}

void TitleState::Enter()
{
	m_pBackground = new Sprite({ 0,0,4200,2240 }, {WIDTH*0.5,HEIGHT*0.5,WIDTH,HEIGHT}, "Img/Background.png", "circles");
	m_pStartGameButton = new TitleButton({0,0,600,200 }, { WIDTH / 2,2 * HEIGHT / 3, 600,200 }, "Img/Button.png", "play");
	FontManager::RegisterFont("Img/8-BIT WONDER.TTF", "title", 80);
	m_pTitle = new Label("title", 60, 60, "Indiana Jones", {75,0,130,255});
	m_pTitle->SetPos(200, 120);
}

void TitleState::Exit()
{
	delete m_pTitle;
	m_pTitle = nullptr;
}

void TitleState::Resume()
{
}

void TitleState::HandleEvents()
{
	
}
