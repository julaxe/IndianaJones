#include "Player.h"
#include "EventManager.h"
#include "MathManager.h"
#include "Engine.h"
#include "Display.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "LevelManager.h"

int Player::m_score = 0;

Player::Player(SDL_Rect s, SDL_FRect d, const char* p, std::string k, int sstart, int smax, int nf) : AnimatedSprite(s, d, p, k, sstart, smax, nf)
{
	m_angle = 0;
	m_type = PLAYER;
	m_scaleRendering = 0.4f;
	m_dst.w = 321 * m_scaleRendering;
	m_dst.h = 488 * m_scaleRendering;
	m_vel = { 0,0 };
	m_acc = { 0,0 };
	m_currentState = PlayerState::JUMP;
	m_jump = 5;
}

void Player::Render()
{
	SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, m_RendererFlip);
}
void Player::Update()
{
	Move(-LevelManager::velocity, 0.0f);
	
	m_vel.x += m_acc.x;
	m_vel.y += m_acc.y;
	

	if (m_vel.x < 0) //Friction X --  Air and earth
	{
		m_vel.x += m_friction;
		m_vel.x = std::fmax(m_vel.x, -10);
		if (m_vel.x > 0)
			m_vel.x = 0;
	}
	else if (m_vel.x > 0)
	{
		m_vel.x -= m_friction;
		m_vel.x = std::fmin(m_vel.x, 10);
		if (m_vel.x < 0)
			m_vel.x = 0;
	}

	if (m_vel.y > 0) // gravity
	{
		m_vel.y = std::fmin(m_vel.y, 30);
	}
	

	m_dst.x += m_vel.x; //move depends on the velocity
	m_dst.y += m_vel.y;

	
	Animate();
	setBoundaries({ 0,0,WIDTH, HEIGHT });
}

void Player::HandleEvents()
{	
	m_collisionBox = { (int)m_dst.x, (int)m_dst.y,(int)(321 * m_scaleRendering),(int)(488 * m_scaleRendering) };
	switch (m_currentState) {
		case PlayerState::IDLE:
			
			if (EVMA::KeyHeld(SDL_SCANCODE_A))
			{
				m_RendererFlip = SDL_FLIP_HORIZONTAL;
				setState(PlayerState::RUN);
			}
			else if (EVMA::KeyHeld(SDL_SCANCODE_D)) 
			{
				m_RendererFlip = SDL_FLIP_NONE;
				setState(PlayerState::RUN);
			}
			else if (EVMA::KeyHeld(SDL_SCANCODE_SPACE))
			{
				setState(PlayerState::JUMP);
				m_acc.y = -m_jump;
			}
			break;
		case PlayerState::RUN:
			
			
			if (EVMA::KeyHeld(SDL_SCANCODE_A)) 
			{
				m_RendererFlip = SDL_FLIP_HORIZONTAL;
				m_acc.x = -5;
				if (EVMA::KeyHeld(SDL_SCANCODE_SPACE))
				{
					setState(PlayerState::JUMP);
					m_acc.y = -m_jump;
				}
			}
			else if (EVMA::KeyHeld(SDL_SCANCODE_D))
			{
				m_RendererFlip = SDL_FLIP_NONE;
				m_acc.x = 5;
				if (EVMA::KeyHeld(SDL_SCANCODE_SPACE))
				{
					setState(PlayerState::JUMP);
					m_acc.y = -m_jump;
				}
			}
			else
				setState(PlayerState::IDLE);
			
			break;
		case PlayerState::JUMP:
			m_acc.y += m_gravity;
			if (CollisionManager::collisionWithBottonTiles(this, LevelManager::m_level))
			{
				setState(PlayerState::IDLE);
			}
			if (EVMA::KeyHeld(SDL_SCANCODE_A))
			{
				m_RendererFlip = SDL_FLIP_HORIZONTAL;
				m_acc.x = -5;
			}
			else if (EVMA::KeyHeld(SDL_SCANCODE_D))
			{
				m_RendererFlip = SDL_FLIP_NONE;
				m_acc.x = 5;
			}
			
			break;
		case PlayerState::SLIDE:
			break;
		case PlayerState::DIE:
			break;
		default:
			break;

	}
	
}

void Player::setState(PlayerState state)
{
	m_currentState = state;
	switch (state)
	{
	case PlayerState::IDLE:
		m_acc.y = 0;
		m_acc.x = 0;
		m_vel.y = 0;

		m_src = { 0 ,600,321,488};
		m_dst.w = 321* m_scaleRendering;
		m_dst.h = 488* m_scaleRendering;
		break;
	case PlayerState::RUN:
		m_vel.y = 0;

		m_src = {0,1626,417,509};
		m_dst.w = 417* m_scaleRendering;
		m_dst.h = 509* m_scaleRendering;
		break;
	case PlayerState::JUMP:
		m_src = {0,1091,409,538};
		m_dst.w = 409 * m_scaleRendering;
		m_dst.h = 538 * m_scaleRendering;
		break;
	case PlayerState::SLIDE:
		m_src = {0,2135,396,391};
		break;
	case PlayerState::DIE:
		m_src = {0,0,588,600};
		break;
	default:
		break;
	}
}

