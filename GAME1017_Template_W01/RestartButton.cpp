#include "RestartButton.h"
#include "StateManager.h"
#include "PlayState.h"
bool RestartButton::pressed = false;
void RestartButton::Execute()
{
	pressed = true;
	STMA::ChangeState(new PlayState());
}
