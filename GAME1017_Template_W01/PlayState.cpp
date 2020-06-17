#include "PlayState.h"
#include "Player.h"
#include "Engine.h"
#include "BackgroundPlayScene.h"
#include <time.h>
#include "Enemy.h"
#include "CollisionManager.h"
#include "AnimationExplosion.h"
#include "SoundManager.h"

PlayState::PlayState()
{
	//Enter();
}

void PlayState::Update()
{
	for (auto d : DisplayList) {
		d->Update();
	}
	CreateEnemies();
	CheckCollision();
}

void PlayState::Render()
{
	for (auto d : DisplayList) {
		d->Render();
	}
}

void PlayState::HandleEvents()
{
	for (int i = 0; i < DisplayList.size();i++) {
		if (DisplayList[i]->GetType() == PLAYER) {
			dynamic_cast<Player*>(DisplayList[i])->HandleEvents(DisplayList);
		}
		else if (DisplayList[i]->GetType() == ENEMY) {
			dynamic_cast<Enemy*>(DisplayList[i])->HandleEvents(DisplayList);
		}
		else {
			DisplayList[i]->HandleEvents();
		}
	}
}

void PlayState::CreateEnemies()
{
	static int timer = 0;
	if (timer > 120) {
		DisplayList.push_back(new Enemy({ 0,0,84,93 }, { WIDTH ,float(rand() % (HEIGHT - 200) + 100) , 50,57} , "Img/enemyRed1.png","Enemy"));
		timer = 0;
	}
	timer++;
}

void PlayState::CheckCollision()
{
	for (int i = 0; i < DisplayList.size(); i++) {
		for (int j = 0; j < DisplayList.size(); j++) {
			//PLAYERLASERS AND ENEMIES
			if (DisplayList[i] != nullptr && DisplayList[j] != nullptr) {
				if (DisplayList[i]->GetType() == PLAYERLASER && DisplayList[j]->GetType() == ENEMY) {
					if (COMA::AABBCheck(*DisplayList[i]->GetDstP(), *DisplayList[j]->GetDstP())) {
						DisplayList.push_back(new AnimationExplosion({ 0,0,32,32 }, { DisplayList[i]->GetDstP()->x,DisplayList[i]->GetDstP()->y,32,32 },
							"Img/explosion.png", "explosion", 0, 6, 4));
						delete DisplayList[i];
						DisplayList[i] = nullptr;
						delete DisplayList[j];
						DisplayList[j] = nullptr;
					}
				}
			}
			//PLAYER AND ENEMIES
			if (DisplayList[i] != nullptr && DisplayList[j] != nullptr) {
				if (DisplayList[i]->GetType() == PLAYER && DisplayList[j]->GetType() == ENEMY) {
					if (COMA::AABBCheck(*DisplayList[i]->GetDstP(), *DisplayList[j]->GetDstP())) {
						delete DisplayList[j];
						DisplayList[j] = nullptr;
					}
				}
			}
			//PLAYER AND ENEMIESLASERS
			if (DisplayList[i] != nullptr && DisplayList[j] != nullptr) {
				if (DisplayList[i]->GetType() == PLAYER && DisplayList[j]->GetType() == ENEMYLASER) {
					if (COMA::AABBCheck(*DisplayList[i]->GetDstP(), *DisplayList[j]->GetDstP())) {
						delete DisplayList[j];
						DisplayList[j] = nullptr;
					}
				}
			}
		}
	}
	DisplayList.erase(std::remove(DisplayList.begin(), DisplayList.end(), nullptr), DisplayList.end());
	//delete if outside screen -> like lasers or enemies
	for (auto it = DisplayList.begin(); it != DisplayList.end(); it++) {
		if ((*it)->checkBoundaries()) {
			delete (*it);
			(*it) = nullptr;
		}
	}
	DisplayList.erase(std::remove(DisplayList.begin(), DisplayList.end(), nullptr), DisplayList.end());

	//delete completed animations
	for (auto it = DisplayList.begin(); it != DisplayList.end(); it++) {
		if ((*it)->GetType() == ANIMATION) {
			if (dynamic_cast<AnimatedSprite*>((*it))->AnimationDone()) {
				delete (*it);
				(*it) = nullptr;
			}
		}
	}
	DisplayList.erase(std::remove(DisplayList.begin(), DisplayList.end(), nullptr), DisplayList.end());
}

void PlayState::Enter()
{
	srand(time(NULL));
	DisplayList.push_back(new BackgroundPlayScene({ 0,0,600,360}, { 0,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background"));
	DisplayList.push_back(new BackgroundPlayScene({ 0,0,600,360}, { WIDTH*1.25,0,WIDTH * 1.3,HEIGHT*2}, "Img/bg.png", "background2"));
	DisplayList.push_back(new  Player({ 0,0,40,57 }, { WIDTH / 3,HEIGHT / 2,40,57 }, "Img/Enemies.png", "player",0, 4, 4));
	SOMA::Load("Aud/moonSonata.wav", "background", SOUND_MUSIC);
	SOMA::PlayMusic("background");
	SOMA::Load("Aud/laser.wav", "laserGreen", SOUND_SFX);
	SOMA::SetAllVolume(5);
}

void PlayState::Exit()
{
}

void PlayState::Resume()
{
}


