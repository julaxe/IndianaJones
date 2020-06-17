#include "PlayState.h"
#include "Player.h"
#include "Engine.h"
#include "BackgroundPlayScene.h"
#include <time.h>
#include "Enemy.h"
#include "CollisionManager.h"
#include "AnimationExplosion.h"
#include "Display.h"

PlayState::PlayState()
{
	//Enter();
}

void PlayState::Update()
{
	for (auto d : Display::Instance()->getList()) {
		d->Update();
	}
	CreateEnemies();
	CheckCollision();
}

void PlayState::Render()
{
	for (auto d : Display::Instance()->getList()) {
		d->Render();
	}
}

void PlayState::HandleEvents()
{
	for (int i = 0; i < Display::Instance()->getList().size();i++) {
		Display::Instance()->getList()[i]->HandleEvents();
	}
}

void PlayState::CreateEnemies()
{
	
	static int timer = 0;
	static int respawnTimer = 120;
	static int iterations = 0;
	if (timer > respawnTimer) {
		Display::Instance()->getList().push_back(new Enemy({ 0,0,84,93 }, { WIDTH ,float(rand() % (HEIGHT - 200) + 100) , 50,57} , "Img/enemyRed1.png","Enemy"));
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
	for (int i = 0; i < Display::Instance()->getList().size(); i++) {
		for (int j = 0; j < Display::Instance()->getList().size(); j++) {
			//PLAYERLASERS AND ENEMIES
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYERLASER && Display::Instance()->getList()[j]->GetType() == ENEMY) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
						Display::Instance()->getList().push_back(new AnimationExplosion({ 0,0,32,32 }, { Display::Instance()->getList()[i]->GetDstP()->x,Display::Instance()->getList()[i]->GetDstP()->y,32,32 },
							"Img/explosion.png", "explosion", 0, 6, 4));
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
					}
				}
			}
			//PLAYER AND ENEMIESLASERS
			if (Display::Instance()->getList()[i] != nullptr && Display::Instance()->getList()[j] != nullptr) {
				if (Display::Instance()->getList()[i]->GetType() == PLAYER && Display::Instance()->getList()[j]->GetType() == ENEMYLASER) {
					if (COMA::AABBCheck(*Display::Instance()->getList()[i]->GetDstP(), *Display::Instance()->getList()[j]->GetDstP())) {
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
}

void PlayState::Enter()
{
	srand(time(NULL));
	Display::Instance()->getList().push_back(new BackgroundPlayScene({ 0,0,600,360}, { 0,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background"));
	Display::Instance()->getList().push_back(new BackgroundPlayScene({ 0,0,600,360}, { WIDTH*1.25,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background2"));
	Display::Instance()->getList().push_back(new  Player({ 0,0,40,57 }, { WIDTH / 3,HEIGHT / 2,40,57 }, "Img/Enemies.png", "player",0, 4, 4));
}

void PlayState::Exit()
{
}

void PlayState::Resume()
{
}


