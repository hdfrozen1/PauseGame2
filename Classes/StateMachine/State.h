#ifndef __STATE_H__
#define __STATE_H__

#include "cocos2d.h"
USING_NS_CC;
class State
{
public:
	virtual void enterState(Node* _owner);
	virtual std::string updateState();
	virtual void exitState();
protected:
	Node* _owner;
};

#endif // !__STATE_H__