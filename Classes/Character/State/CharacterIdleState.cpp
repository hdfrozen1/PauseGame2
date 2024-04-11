#include "CharacterIdleState.h"
#include "KeyBoardInput.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
void CharacterIdleState::enterState(Node* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(static_cast<Character*>(_owner)->getName() + "-Idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	static_cast<Character*>(_owner)->getModel()->runAction(animate);
}

std::string CharacterIdleState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();
	Vec2 direction = keyboard->getDirection();
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_W))
	{
		return "Jump";
	}

	if (direction.x != 0 && direction.y == 0)
	{
		return "Run";
	}

	if (direction.y < 0)
	{
		return "Fall";
	}

	return "Idle";
}

void CharacterIdleState::exitState()
{
	State::exitState();
}
