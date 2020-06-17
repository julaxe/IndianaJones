#include "TitleButton.h"
#include "StateManager.h"
#include "PlayState.h"

void TitleButton::Execute()
{
	STMA::ChangeState(new PlayState());
}
