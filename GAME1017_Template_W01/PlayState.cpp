#include "PlayState.h"
#include "Player.h"
#include "Engine.h"
#include "Background.h"
#include <time.h>
#include "CollisionManager.h"
#include "AnimationExplosion.h"
#include "Display.h"
#include "SoundManager.h"
#include "ScoreLabel.h"
#include "FontManager.h"
#include "EventManager.h"
#include "StateManager.h"
#include "PauseState.h"
#include "LoseState.h"
#include "DebugManager.h"
#include "LevelManager.h"

bool PlayState::m_pause = false;
Display* Display::m_Instance = nullptr;
PlayState::PlayState()
{
	//Enter();
}

void PlayState::Update()
{
	if (!m_pause) {
		Display::Instance()->Update();
		LevelManager::UpdateLevel();
	}
}

void PlayState::Render()
{
	
	Display::Instance()->Render();
	for (int i = 0; i < Display::Instance()->getListLabels().size(); i++) {
		Display::Instance()->getListLabels()[i]->Render();
	}
	if (m_debugView)
	{
		for (auto p : Display::Instance()->getPlayers()->getList())
		{
			DEMA::DrawRect(p->getCollisionBox(), { 255,255,255,255 });

		}
		LevelManager::DrawCollisionBoxes();
	}
}

void PlayState::HandleEvents()
{
	if (!m_pause) {
		Display::Instance()->HandleEvents();
	}
	if (EVMA::KeyReleased(SDL_SCANCODE_P) || EVMA::KeyReleased(SDL_SCANCODE_RETURN)) {
		if (!m_pause) {
			STMA::PushState(new PauseState());
		}
		else {
			STMA::PopState();
		}
		m_pause = !m_pause;
	}
	if (EVMA::KeyReleased(SDL_SCANCODE_H)) {
		m_debugView = !m_debugView;
	}
}


void PlayState::Enter()
{
	Player::m_score = 0;
	m_pause = false;
	//init Labels
	FOMA::RegisterFont("Img/alpha_echo.ttf", "alpha", 40);
	srand(time(NULL));

	//BACKGROUNDS
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,600,360}, { 0,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background", 1));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,600,360}, { WIDTH*1.25,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background2",1));
	LevelManager::GenerateTiles();

	//PLAYER
	Display::Instance()->getPlayers()->getList().push_back(new  Player({ 0,600,321,486 }, { WIDTH / 3,HEIGHT / 2,321,486 }, "Img/IndianaJones.png", "player",0, 10, 5));
	
	//LABELS
	Display::Instance()->getListLabels().push_back(new ScoreLabel("alpha", 10, 10, "SCORE: "));
	
	//SOUND
	SOMA::Load("Aud/moonSonata.wav", "background", SOUND_MUSIC);
	SOMA::PlayMusic("background");
	SOMA::Load("Aud/laser.wav", "laserGreen", SOUND_SFX);
	SOMA::SetAllVolume(5);

}

void PlayState::Exit()
{
	//Display::Instance()->getList().clear();
}

void PlayState::Resume()
{
}


