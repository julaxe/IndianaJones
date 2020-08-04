#include "Player.h"
#include "EventManager.h"
#include "MathManager.h"
#include "Engine.h"
#include "Display.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "LevelManager.h"
#include "TextureManager.h"

int Player::m_score = 0;

Player::Player(SDL_Rect s, SDL_FRect d, const char* p, std::string k, AnimationParameters animationP) : AnimatedSprite(s, d, p, k, animationP)
{
	m_type = PLAYER;
	m_scaleRendering = 4.0f;
	m_dst.w = 50 * m_scaleRendering;
	m_dst.h = 37 * m_scaleRendering;
	m_jumpISpeed = 15.0f;
	m_runningISpeed = 10.0f;
	m_slidingISpeed = 7.0f;
	m_maxVelX = 10.0f;
	m_maxVelY = 30.0f;
	
	updateCollisionBox(40.0f, 90.0f, 50.0f);
	setState(PlayerState::IDLE);
}

void Player::Render()
{
	SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, m_RendererFlip);
}
void Player::Update()
{
	m_vel.x += m_acc.x;
	m_vel.y += m_acc.y;
	

	if (m_vel.x < 0) //Friction X --  Air and earth
	{
		m_vel.x += m_friction;
		m_vel.x = std::fmax(m_vel.x, -m_maxVelX);
		if (m_vel.x > 0)
			m_vel.x = 0;
	}
	else if (m_vel.x > 0)
	{
		m_vel.x -= m_friction;
		m_vel.x = std::fmin(m_vel.x, m_maxVelX);
		if (m_vel.x < 0)
			m_vel.x = 0;
	}

	if (m_vel.y > 0) // gravity
	{
		m_vel.y = std::fmin(m_vel.y, m_maxVelY);
	}

	Move(m_vel.x - LevelManager::velocity, m_vel.y);//move depends on the velocity
	if (checkBoundaries({ 0,0,WIDTH, HEIGHT }))
	{
		Move(-m_vel.x + LevelManager::velocity, 0.0f);
	}
	
	Animate();

}

void Player::HandleEvents()
{	
	switch (m_currentState) {
		case PlayerState::IDLE:
						if (MoveIfInput())
						{
							setState(PlayerState::RUN);
						}
						else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
						{
							setState(PlayerState::JUMP);
				
						}
						else if (EVMA::KeyHeld(SDL_SCANCODE_LCTRL))
						{
							setState(PlayerState::DUCK);

						}
						else if (EVMA::KeyHeld(SDL_SCANCODE_T))
						{
							setState(PlayerState::DIE);
						}
						break;
		case PlayerState::RUN:
						if(!MoveIfInput())
							setState(PlayerState::IDLE);
						else //if you are stil running
						{
							if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
							{
								setState(PlayerState::JUMP);
							}
							if (EVMA::KeyPressed(SDL_SCANCODE_LCTRL))
							{
								setState(PlayerState::SLIDE);
							}
						}
						break;
		case PlayerState::JUMP:
						m_acc.y = m_gravity;
						jumpingStateMachine();
						if (m_currentJumpingState != JumpingState::PREPARING)
						{
							MoveIfInput();
						}
						break;
		case PlayerState::DUCK:
						if (!EVMA::KeyHeld(SDL_SCANCODE_LCTRL))
						{
							setState(PlayerState::IDLE);
						}
						break;
		case PlayerState::SLIDE:
						if (m_RendererFlip == SDL_FLIP_NONE)
							m_vel.x = m_slidingISpeed;
						else
							m_vel.x = -m_slidingISpeed;

						if (AnimationDone())
						{
							setState(PlayerState::IDLE);
						}
						break;
		case PlayerState::DIE:
						if (AnimationDone())
						{
							m_frame = m_params->nf + 1;
						}
						if (EVMA::KeyHeld(SDL_SCANCODE_R))
						{
							setState(PlayerState::IDLE);
						}
						break;
		default:
			break;

	}
	
}

void Player::setState(PlayerState state)
{
	m_currentState = state;
	m_pText = TEMA::GetTexture("player");
	switch (state)
	{
	case PlayerState::IDLE:
		m_acc.y = 0;
		m_acc.x = 0;
		m_vel.y = 0;
		updateCollisionBox(40.0f,90.0f);
		
		m_src = { 0 ,0,50,37};
		m_params = new AnimationParameters(0, 3, 10, 0, 6, (int)m_src.y);
		
		break;
	case PlayerState::RUN:
		m_vel.y = 0;

		m_src = {0,37,50,37};
		m_params = new AnimationParameters(1, 6, 10, 0, 6, (int)m_src.y);

		break;
	case PlayerState::JUMP:
		setJumpingState(JumpingState::PREPARING);
		break;
	case PlayerState::DUCK:

		m_pText = TEMA::GetTexture("player2");
		m_src = { 0,259,50,37 };
		m_params = new AnimationParameters(3, 3, 10, 0, 6, (int)m_src.y);
		break;
	case PlayerState::SLIDE:
		updateCollisionBox(90.0f, 30.0f);
		m_src = { 0,111,50,37 };
		m_params = new AnimationParameters(3, 0, 10, 1, 6, (int)m_src.y);
		break;
	case PlayerState::DIE:

		m_pText = TEMA::GetTexture("player2");
		m_src = { 0,148,50,37 };
		m_params = new AnimationParameters(4, 4, 10, 1, 6, (int)m_src.y);
	default:
		break;
	}
	m_currentRow = 0;
	m_frame = 0;
	m_sprite = m_params->sstart;

}

void Player::setJumpingState(JumpingState state)
{
	m_currentJumpingState = state;
	switch (m_currentJumpingState)
	{
	case JumpingState::PREPARING:
		m_src = { 0,74,50,37 };

		m_params = new AnimationParameters(0, 1, 6, 0, 6, (int)m_src.y);
		break;
	case JumpingState::RISING:
		m_vel.y = -m_jumpISpeed;
		if (EventManager::KeyHeld(SDL_SCANCODE_SPACE))
			m_vel.y = -m_jumpISpeed * 1.3f;
		m_src = { 0,74,50,37 };

		m_params = new AnimationParameters(2, 3, 10, 0, 6, (int)m_src.y);
		break;
	case JumpingState::FLOATING:
		m_src = { 0,74,50,37 };

		m_params = new AnimationParameters(4, 1, 5, 1, 6, (int)m_src.y);
		break;
	case JumpingState::FALLING:
		m_src = { 0,111,50,37 };

		m_params = new AnimationParameters(1, 2, 10, 0, 6, (int)m_src.y);
		break;
	default:
		break;
	}
	m_currentRow = 0;
	m_frame = 0;
	m_sprite = m_params->sstart;
}

bool Player::MoveIfInput()
{
	bool move = false;
	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		m_RendererFlip = SDL_FLIP_HORIZONTAL;
		m_vel.x = -m_runningISpeed;
		move = true;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		m_RendererFlip = SDL_FLIP_NONE;
		m_vel.x = m_runningISpeed;
		move = true;
	}
	return move;
}

void Player::jumpingStateMachine()
{
	switch (m_currentJumpingState)
	{
	case JumpingState::PREPARING:
		m_acc.x = 0;
		m_acc.y = 0;
		if (AnimationDone())
		{
			setJumpingState(JumpingState::RISING);
		}
		break;
	case JumpingState::RISING:
		if (m_vel.y > -2)
		{
			setJumpingState(JumpingState::FLOATING);
		}
		break;
	case JumpingState::FLOATING:
		if (m_vel.y > 2)
		{
			setJumpingState(JumpingState::FALLING);

		}
		break;
	case JumpingState::FALLING:
		if (CollisionManager::collisionWithBottonTiles(this, LevelManager::m_level))
		{
			setState(PlayerState::IDLE);
		}
		break;
	default:
		break;
	}
}
