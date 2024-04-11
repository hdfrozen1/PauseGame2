#include "CharacterJumpState.h"
#include "StateMachine/StateMachine.h"
#include "KeyBoardInput.h"
#include "Character/Character.h"

void CharacterJumpState::enterState(Node* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(static_cast<Character*>(_owner)->getName() + "-Jump");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	static_cast<Character*>(_owner)->getModel()->runAction(animate);
}

std::string CharacterJumpState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();
	// update
	Vec2 direction = keyboard->getDirection();
	auto character = static_cast<Character*>(_owner);
	if (character->isOnGround) {
		static_cast<Character*>(_owner)->getPhysicsBody()->setVelocity(Vec2(_owner->getPhysicsBody()->getVelocity().x, 100));
	}
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_A)) {
		static_cast<Character*>(_owner)->getPhysicsBody()->setVelocity(Vec2(-40, _owner->getPhysicsBody()->getVelocity().y));
	}
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_D)) {
		static_cast<Character*>(_owner)->getPhysicsBody()->setVelocity(Vec2(40, _owner->getPhysicsBody()->getVelocity().y));
	}

	if (direction.x != 0)
		static_cast<Character*>(_owner)->getModel()->setFlippedX(direction.x < 0);

	if (keyboard->getDirection() == Vec2::ZERO)
	{
		return "Idle";
	}
	if (direction.x != 0 && direction.y == 0)
	{
		return "Run";
	}
	if (direction.y < 0) {
		return "Fall";
	}
	return "Jump";
}

void CharacterJumpState::exitState()
{
	State::exitState();
}