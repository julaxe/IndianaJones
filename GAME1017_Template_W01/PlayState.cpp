#include "PlayState.h"
#include "Player.h"
#include "Engine.h"
#include "Background.h"
#include <time.h>
#include "Enemy.h"
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
#include "EnemyMeteor.h"
#include "Enemy2.h"

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
	
		CreateEnemies();
		CheckCollision();
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

void PlayState::CreateEnemies()
{
	
	static int timer = 0;
	static int respawnTimer = 120;
	static int iterations = 0;
	int randomNumber = rand() % 100;
	if (timer > respawnTimer) {
		if (randomNumber < 50) { //Creation Enemy1
			Display::Instance()->getList().push_back(new Enemy({ 0,0,84,93 }, { WIDTH ,float(rand() % (HEIGHT - 200) + 100) , 50,57} , "Img/enemyRed1.png","Enemy"));
		}
		else if (randomNumber >= 50 && randomNumber < 80) { //Creation Meteor
			Display::Instance()->getList().push_back(new EnemyMeteor({ 280,214,75,60 }, { WIDTH ,float(rand() % (HEIGHT - 200) + 100) , 75,66}, "Img/Enemies.png", "EnemyMeteor"));
		}
		else if (randomNumber >= 80 && randomNumber < 100) { //Creation Enemy2
			Display::Instance()->getList().push_back(new Enemy2({ 0,0,75,99 }, { WIDTH ,float(rand() % (HEIGHT - 200) + 100) , 45,57 }, "Img/Enemy2.png", "Enemy2"));
		}
			timer = 0;
			iterations++;
	}
	if (respawnTimer >= 60) {
		if (iterations >= 5) {
			respawnTimer -= 5;
			iterations = 0;
		}
	}
	timer++;
}

void PlayState::CheckCollision()
{
	bool GameOver = false;
	for (int i = 0; i < Display::Instance()->getList().size(); i++) {
		for (int j = 0; j < Display::Instance()->getList().size(); j++) {
			//PLAYERLASERS AND ENEMIES
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYERLASER && Display::Instance()->getList()[j]->GetType() == ENEMY) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						Display::Instance()->getList().push_back(new AnimationExplosion({ 0,0,32,32 }, { Display::Instance()->getList()[i]->GetDstP()->x,Display::Instance()->getList()[i]->GetDstP()->y,32,32 },
							"Img/explosion.png", "explosion", 0, 6, 4));
						Player::m_score += 20;
						delete Display::Instance()->getList()[i];
						Display::Instance()->getList()[i] = nullptr;
						delete Display::Instance()->getList()[j];
						Display::Instance()->getList()[j] = nullptr;
					}
				}
			}
			//PLAYER AND ENEMIES
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYER && Display::Instance()->getList()[j]->GetType() == ENEMY) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						delete Display::Instance()->getList()[j];
						Display::Instance()->getList()[j] = nullptr;
						GameOver = true;
					}
				}
			}
			//PLAYER AND ENEMIESLASERS
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYER && Display::Instance()->getList()[j]->GetType() == ENEMYLASER) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						delete Display::Instance()->getList()[j];
						Display::Instance()->getList()[j] = nullptr;
						GameOver = true;
					}
				}
			}
			//PLAYERLASER AND METEORS
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYERLASER && Display::Instance()->getList()[j]->GetType() == ENEMYMETEOR) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						Display::Instance()->getList().push_back(new AnimationExplosion({ 0,0,32,32 }, { Display::Instance()->getList()[i]->GetDstP()->x,Display::Instance()->getList()[i]->GetDstP()->y,32,32 },
							"Img/explosion.png", "explosion", 0, 6, 4));
						delete Display::Instance()->getList()[i];
						Display::Instance()->getList()[i] = nullptr;
					}
				}
			}
			//PLAYER AND METEORS
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYER && Display::Instance()->getList()[j]->GetType() == ENEMYMETEOR) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						delete Display::Instance()->getList()[j];
						Display::Instance()->getList()[j] = nullptr;
						GameOver = true;
					}
				}
			}
			//PLAYER AND ENEMY2
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYER && Display::Instance()->getList()[j]->GetType() == ENEMY2) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						delete Display::Instance()->getList()[j];
						Display::Instance()->getList()[j] = nullptr;
						GameOver = true;
					}
				}
			}
			//PLAYERLASERS AND ENEMY2
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYERLASER && Display::Instance()->getList()[j]->GetType() == ENEMY2) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						Display::Instance()->getList().push_back(new AnimationExplosion({ 0,0,32,32 }, { Display::Instance()->getList()[i]->GetDstP()->x,Display::Instance()->getList()[i]->GetDstP()->y,32,32 },
							"Img/explosion.png", "explosion", 0, 6, 4));
						Player::m_score += 20;
						delete Display::Instance()->getList()[i];
						Display::Instance()->getList()[i] = nullptr;
						delete Display::Instance()->getList()[j];
						Display::Instance()->getList()[j] = nullptr;
					}
				}
			}
		}
	}
	Display::Instance()->getList().erase(std::remove(Display::Instance()->getList().begin(), Display::Instance()->getList().end(), nullptr), Display::Instance()->getList().end());
	//delete if outside screen -> like lasers or enemies
	for (auto it = Display::Instance()->getList().begin(); it != Display::Instance()->getList().end(); it++) {
		if ((*it)->checkBoundaries()) {
			delete (*it);
			(*it) = nullptr;
		}
	}
	Display::Instance()->getList().erase(std::remove(Display::Instance()->getList().begin(), Display::Instance()->getList().end(), nullptr), Display::Instance()->getList().end());
	Display::Instance()->getList().shrink_to_fit();
	//delete completed animations
	for (auto it = Display::Instance()->getList().begin(); it != Display::Instance()->getList().end(); it++) {
		if ((*it)->GetType() == ANIMATION) {
			if (dynamic_cast<AnimatedSprite*>((*it))->AnimationDone()) {
				delete (*it);
				(*it) = nullptr;
			}
		}
	}
	Display::Instance()->getList().erase(std::remove(Display::Instance()->getList().begin(), Display::Instance()->getList().end(), nullptr), Display::Instance()->getList().end());
	if (GameOver) {
		STMA::ChangeState(new LoseState());
	}
}

void PlayState::Enter()
{
	Player::m_score = 0;
	Enemy::m_vel = 20;
	Enemy::iterations = 0;
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


