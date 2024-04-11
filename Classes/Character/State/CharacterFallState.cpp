#include "CharacterFallState.h"
#include "StateMachine/StateMachine.h"
#include "KeyBoardInput.h"
#include "Character/Character.h"

void CharacterFallState::enterState(Node* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(static_cast<Character*>(_owner)->getName() + "-Fall");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	static_cast<Character*>(_owner)->getModel()->runAction(animate);
}

std::string CharacterFallState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();
	// update
	Vec2 direction = keyboard->getDirection();
	static_cast<Character*>(_owner)->getPhysicsBody()->applyForce(direction * 60);

	if (direction.x != 0) {
		static_cast<Character*>(_owner)->getModel()->setFlippedX(direction.x < 0);
	}
	if (keyboard->getDirection() == Vec2::ZERO)
	{
		return "Idle";
	}
	if (direction.x != 0 && direction.y == 0)
	{
		return "Run";
	}
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_A)) 
	{
		return "Jump";
	}
	return "Fall";
}

void CharacterFallState::exitState()
{
	State::exitState();
}