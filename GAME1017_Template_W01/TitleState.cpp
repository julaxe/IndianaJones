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
	m_pBackground = new Sprite({ 0,0,900,627 }, {450,300,900,627}, "Img/StarQuest.jpg", "circles");
	m_pStartGameButton = new TitleButton({0,0,400,100 }, { WIDTH / 2,2 * HEIGHT / 3,200,50 }, "Img/play.png", "play");
	FontManager::RegisterFont("Img/BerkshireSwash-Regular.ttf", "title", 80);
	m_pTitle = new Label("title", 60, 60, "Space Odissey 2.0", {192,192,192,192});
	m_pTitle->SetPos(95, 60);
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
