#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "stdafx.h"
#include <vector>

using namespace std;

class IState;

class StateManager
{
private:
	static StateManager* mStateManager;
	vector<IState*> mStates;
	// This is a singleton, so our constructor is private.
	StateManager();

public:
	~StateManager();
	static StateManager* Instance();
	//void Start(IState *state);
	void ChangeState(IState *state);
	void PushState(IState *state);
	void PopState(IState *state);
};
#endif
