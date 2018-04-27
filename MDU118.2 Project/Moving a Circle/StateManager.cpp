#include "stdafx.h"
#include "StateManager.h"

using namespace std;

// Initialise our static member variable.
StateManager* StateManager::mStateManager = 0;

StateManager::StateManager()
{
	// Constructor
}

StateManager::~StateManager()
{
	// Destructor
}

StateManager * StateManager::Instance()
{
	if (mStateManager == 0)
	{
		StateManager* mstateManager = new StateManager;
	}
	return mStateManager;
}

void StateManager::ChangeState(IState * state)
{

}

void StateManager::PushState(IState * state)
{

}

void StateManager::PopState(IState * state)
{

}
