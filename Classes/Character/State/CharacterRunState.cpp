#include "CharacterRunState.h"
#include "StateMachine/StateMachine.h"
#include "KeyBoardInput.h"
#include "Character/Character.h"

void CharacterRunState::enterState(Node* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(static_cast<Character*>(_owner)->getName() + "-Run");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	static_cast<Character*>(_owner)->getModel()->runAction(animate);
}

std::string CharacterRunState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();
	// update
	Vec2 direction = keyboard->getDirection();
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_A)) {
		static_cast<Character*>(_owner)->getPhysicsBody()->setVelocity(Vec2(-40, (_owner->getPhysicsBody()->getVelocity().y)) );
	}
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_D)) {
		static_cast<Character*>(_owner)->getPhysicsBody()->setVelocity(Vec2(40, _owner->getPhysicsBody()->getVelocity().y) );
	}

	if (direction.x != 0)
		static_cast<Character*>(_owner)->getModel()->setFlippedX(direction.x < 0);

	if (keyboard->getDirection() == Vec2::ZERO)
	{
		return "Idle";
	}
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_W))
	{
		return "Jump";
	}
	if (direction.y < 0) {
		return "Fall";
	}
	return "Run";
}

void CharacterRunState::exitState()
{
	State::exitState();
}