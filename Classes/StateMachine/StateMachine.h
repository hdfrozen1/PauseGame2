#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "cocos2d.h"
#include "State.h"
#include "unordered_map"

USING_NS_CC;


class StateMachine : public Node
{
public:
	static const int AnimationTag = 1;
public:
	static StateMachine* create(Node* owner);
	bool init(Node* owner);

	void addState(std::string stateName, State* newState);
	void setCurrentState(std::string stateName);

protected:
	std::unordered_map<std::string, State*> _states;
	std::string _currentState;
	Node* _owner;
protected:
	void update(float dt) override;
	void onEnter() override;
};

#endif // !__STATE_MACHINE_H__