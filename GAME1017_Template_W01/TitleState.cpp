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
	m_pBackground = new Sprite({ 0,0,900,627 }, {WIDTH*0.5,HEIGHT*0.5,WIDTH,HEIGHT}, "Img/StarQuest.jpg", "circles");
	m_pStartGameButton = new TitleButton({0,0,150,50 }, { WIDTH / 2,2 * HEIGHT / 3,200,50 }, "Img/startButton.png", "play");
	FontManager::RegisterFont("Img/BerkshireSwash-Regular.ttf", "title", 80);
	m_pTitle = new Label("title", 60, 60, "Space Odissey 2.0", {192,192,192,192});
	m_pTitle->SetPos(95, 60);
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
