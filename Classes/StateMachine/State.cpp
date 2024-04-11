#include "State.h"
#include "Character/Character.h"
void State::enterState(Node* _owner)
{
	this->_owner = _owner;
}

std::string State::updateState()
{
	return std::string();
}

void State::exitState()
{
	static_cast<Character*>(_owner)->getModel()->stopAllActions();
}