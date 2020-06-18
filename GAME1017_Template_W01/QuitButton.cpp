#include "QuitButton.h"
#include "StateManager.h"
#include "LoseState.h"

bool QuitButton::pressed = false;
void QuitButton::Execute() 
{
	STMA::ChangeState(new LoseState);
	pressed = true;
}
