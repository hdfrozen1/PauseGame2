#ifndef __CHARACTER_JUMP_STATE_H__
#define __CHARACTER_JUMP_STATE_H__

#include "StateMachine/State.h"


class CharacterJumpState : public State
{
public:
	void enterState(Node* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__CHARACTER_JUMP_STATE_H__