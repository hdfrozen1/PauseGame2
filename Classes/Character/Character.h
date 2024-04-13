#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
USING_NS_CC;
#include "StateMachine/StateMachine.h"

class Character : public Node
{
public:
	static Character* create(std::string file,float scale);

	bool init(std::string file,float scale);
	Sprite* getModel() { return _model; }
	std::string getName() { return _thefile; }
	bool isOnGround;
	bool isJumping;
	bool isOnBox;
	float getDefaultScale() { return _defaultScale; }
	bool isonCam() { return _isOnCam; }
protected:
	bool loadAnimations();
	Sprite* _model;
	StateMachine* _stateMachine;
	std::string _thefile;
	bool callbackOnContactBegin(PhysicsContact& contact);
	bool callbackOnContactSeparate(PhysicsContact& contact);
	Node* feetNode;
	Node* boxNode;
	PhysicsBody* body;
	PhysicsBody* bodyGround;
	void update(float dt) override;
	float delta;
	void onEnter() override;
	bool _isOnCam;
	float _defaultScale;
};

#endif // !__CHARACTER_H__