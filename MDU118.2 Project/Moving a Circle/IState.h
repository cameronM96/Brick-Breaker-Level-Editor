#ifndef ISTATE_H
#define ISTATE_H

#include "stdafx.h"
#include "StateManager.h"

using namespace std;

class IState
{
protected:
public:
	IState();
	virtual ~IState();

	//Executed at the beginning of each state.
	virtual void Enter() = 0;
	//Executed at the end of each state.
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	// Removes the current state from the stack and add a new State
	virtual void ChangeState(IState *state);
	// Pause the current state and add a new state to the end of the stack.
	virtual void PushState(IState *state);
	// Remove the last state on the stack and set the current state to the 
	// previous state on the stack.
	virtual void PopState(IState *state);
};

#endif // !ISTATE_H
