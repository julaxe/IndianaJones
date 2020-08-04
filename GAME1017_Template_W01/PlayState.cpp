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
#include "TextureManager.h"
#include "Skeleton.h"

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
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536}, { 0,0,WIDTH * 1.1,HEIGHT}, "Img/background01.png", "background", 0.2));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH*1.1,0,WIDTH * 1.1,HEIGHT}, "Img/background01.png", "background2", 0.2));

	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { 0,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_005.png", "background3", 0.4));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH * 1.1,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_005.png", "background4", 0.4));

	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { 0,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_004.png", "background5", 0.6));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH * 1.1,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_004.png", "background6", 0.6));

	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { 0,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_003.png", "background7", 0.8));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH * 1.1,0,WIDTH * 1.1,HEIGHT}, "Img/fantasy-2048-x-1536_003.png", "background8", 0.8));

	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { 0,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_002.png", "background9", 1));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH * 1.1,0,WIDTH * 1.1,HEIGHT}, "Img/fantasy-2048-x-1536_002.png", "background10", 1));

	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { 0,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_001.png", "background11", 1.2));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH * 1.1,0,WIDTH * 1.1,HEIGHT}, "Img/fantasy-2048-x-1536_001.png", "background12", 1.2));

	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { 0,0,WIDTH * 1.1,HEIGHT  }, "Img/fantasy-2048-x-1536_000.png", "background13", 1.4));
	Display::Instance()->getBackground()->getList().push_back(new Background({ 0,0,2048,1536 }, { WIDTH * 1.1,0,WIDTH * 1.1,HEIGHT }, "Img/fantasy-2048-x-1536_000.png", "background14", 1.4));


	LevelManager::GenerateTiles();

	//PLAYER
	AnimationParameters params(0, 3, 10, 0, 6,0);
	TEMA::RegisterTexture("Img/adventurer2.png", "player2");
	Display::Instance()->getPlayers()->getList().push_back(new  Player({ 0,0,50,37 }, { WIDTH / 3,HEIGHT*0.95 ,321,486 }, "Img/adventurer1.png", "player", params));

	Display::Instance()->getEnemies()->getList().push_back(new  Skeleton({ 0,0,22,33 }, { WIDTH *1.2,HEIGHT*0.95,321,600 }, "Img/skeletonSheet.png", "skeleton", params));
	
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


