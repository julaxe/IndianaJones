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


bool PlayState::m_pause = false;
PlayState::PlayState()
{
	//Enter();
}

void PlayState::Update()
{
	if (!m_pause) {
		for (int i = 0; i < Display::Instance()->getList().size(); i++) {
			Display::Instance()->getList()[i]->Update();
		}
		for (int i = 0; i < Display::Instance()->getListLabels().size(); i++) {
			Display::Instance()->getListLabels()[i]->Update();
		}
	}
}

void PlayState::Render()
{
	for (int i = 0; i < Display::Instance()->getList().size(); i++) {
		Display::Instance()->getList()[i]->Render();
	}
	for (int i = 0; i < Display::Instance()->getListLabels().size(); i++) {
		Display::Instance()->getListLabels()[i]->Render();
	}
}

void PlayState::HandleEvents()
{
	if (!m_pause) {
		for (int i = 0; i < Display::Instance()->getList().size(); i++) {
			Display::Instance()->getList()[i]->HandleEvents();
		}
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
}


void PlayState::Enter()
{
	Player::m_score = 0;
	m_pause = false;
	//init Labels
	FOMA::RegisterFont("Img/alpha_echo.ttf", "alpha", 40);
	srand(time(NULL));

	//BACKGROUND AND PLAYER -- initial elements
	Display::Instance()->getList().push_back(new Background({ 0,0,600,360}, { 0,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background", 1));
	Display::Instance()->getList().push_back(new Background({ 0,0,600,360}, { WIDTH*1.25,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background2",1));
	Display::Instance()->getList().push_back(new  Player({ 0,0,40,57 }, { WIDTH / 3,HEIGHT / 2,40,57 }, "Img/Enemies.png", "player",0, 4, 4));
	
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
	Display::Instance()->getList().clear();
}

void PlayState::Resume()
{
}


