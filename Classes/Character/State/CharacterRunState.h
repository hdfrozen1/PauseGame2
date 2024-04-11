#ifndef __CHARACTER_RUN_STATE_H__
#define __CHARACTER_RUN_STATE_H__

#include "StateMachine/State.h"


class CharacterRunState : public State
{
public:
	void enterState(Node* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__CHARACTER_RUN_STATE_H__