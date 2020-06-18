#include "EscapeButton.h"
#include "Engine.h"

bool EscapeButton::pressed = false;
void EscapeButton::Execute()
{
	Engine::Instance().Running() = false;
}
