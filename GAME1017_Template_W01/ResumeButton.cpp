#include "ResumeButton.h"
#include "StateManager.h"
#include "PlayState.h"

void ResumeButton::Execute()
{
	STMA::PopState();
	PlayState::m_pause = !PlayState::m_pause;
}
