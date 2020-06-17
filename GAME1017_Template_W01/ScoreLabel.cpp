#include "ScoreLabel.h"
#include "Display.h"
#include "Player.h"
#include <string>
void ScoreLabel::Update()
{
	std::string str = "SCORE: " + std::to_string(Player::m_score);
	SetText(str.c_str());
	
}
