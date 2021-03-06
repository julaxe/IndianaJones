#include "StateManager.h"

void StateManager::Update()
{
	if (!s_states.empty()) {
		for (auto s : s_states) {
			s->Update();
		}
	}
}

void StateManager::Render()
{
	if (!s_states.empty()) {
		for (auto s : s_states) {
			s->Render();
		}
	}
}

void StateManager::PushState(State * pState)
{
	s_states.push_back(pState); // push_back() is a method of the vector type.
	s_states.back()->Enter();
}

void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty())
	{
		for (auto s : s_states) {

			s->Exit();
			delete s; // De-allocating the state in the heap.
			s = nullptr; // Nullifying pointer to the de-allocated state.
		}
			s_states.clear(); // Removes the now-null pointer from the vector.
	}
	pState->Enter();
	s_states.push_back(pState);
}

void StateManager::PopState()
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	s_states.back()->Resume();
}

void StateManager::Quit()
{
	while (!s_states.empty())	// Because we can exit the game in the pause state with the window's 'X'.
	{							// Ensures that ALL states left in the vector are cleaned up.
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates(){	return s_states; }

std::vector<State*> StateManager::s_states;