#include "Player.h"
#include "EventManager.h"
#include "MathManager.h"
#include "Engine.h"
#include "Display.h"
#include "SoundManager.h"

int Player::m_score = 0;
void Player::Update()
{
	Animate();
	setBoundaries({ 0,0,WIDTH / 2, HEIGHT });
}

void Player::HandleEvents()
{	
	Move();
	
}

void Player::setMovement(Directions direction)
{
	int velX = 20;
	int velY = 40;
	switch (direction)
	{
	case LEFT:
		m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - velX, 0.1);
		break;
	case RIGHT:
		m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x + velX, 0.1);
		break;
	case UP:
		m_dst.y = MAMA::LerpD(m_dst.y, m_dst.y - velY, 0.1);
		break;
	case DOWN:
		m_dst.y = MAMA::LerpD(m_dst.y, m_dst.y + velY, 0.1);
		break;
	default:
		break;
	}
}

void Player::Move()
{
	if (EVMA::KeyHeld(SDL_SCANCODE_LEFT) || EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		setMovement(LEFT);
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_RIGHT) || EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		setMovement(RIGHT);
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_UP) || EVMA::KeyHeld(SDL_SCANCODE_W))
	{
		setMovement(UP);
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_DOWN) || EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		setMovement(DOWN);
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_LEFT) || EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		if (m_frame > 12) m_frame = 0;
		m_frameMax = 12;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_RIGHT) || EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		if (m_frame > 4) m_frame = 0;
		m_frameMax = 4;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_UP) || EVMA::KeyHeld(SDL_SCANCODE_W))
	{
		if (m_frame > 8) m_frame = 0;
		m_frameMax = 8;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_DOWN) || EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		if (m_frame > 8) m_frame = 0;
		m_frameMax = 8;
	}
	else 
	{
		if (m_frame > 8) m_frame = 0;
		m_frameMax = 8;
	}
}
