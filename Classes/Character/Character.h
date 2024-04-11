#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
USING_NS_CC;
#include "StateMachine/StateMachine.h"

class Character : public Node
{
public:
	static Character* create(std::string file);

	bool init(std::string file);
	Sprite* getModel() { return _model; }
	std::string getName() { return _thefile; }
protected:
	bool loadAnimations();
	Sprite* _model;
	StateMachine* _stateMachine;
	std::string _thefile;

};

#endif // !__CHARACTER_H__