#pragma once
#ifndef SRC_STATEMACHINE_H_
#define SRC_STATEMACHINE_H_
#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine {
public:
	StateMachine() {}
	~StateMachine() {}

	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChanges();

	StateRef &GetActiveState();

private:
	std::stack<StateRef> _states;
	StateRef _newState;

	bool _isRemoving = false;
	bool _isAdding = false;
	bool _isReplacing = false;
};

#endif /* SRC_STATEMACHINE_H_ */