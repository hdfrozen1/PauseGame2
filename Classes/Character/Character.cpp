#include "Character.h"
#include "AnimationUtils/AnimationUtils.h"
#include "State/CharacterFallState.h"
#include "State/CharacterJumpState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"
#include "DefineBitmask.h"
class StateMachine;

Character* Character::create(std::string file)
{
    auto newObject = new Character();
    if (newObject != nullptr && newObject->init(file))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Character::init(std::string file)
{
    if (!Node::init())
    {
        log("Init Entity failed!");
        return false;
    }
    
    this->_thefile = file;
    loadAnimations();
    _model = Sprite::createWithSpriteFrameName(_thefile + "-Idle (1)");
    this->addChild(_model);

    _stateMachine = StateMachine::create(this);
    _stateMachine->addState("Idle", new CharacterIdleState());
    _stateMachine->addState("Jump", new CharacterJumpState());
    _stateMachine->addState("Run", new CharacterRunState());
    _stateMachine->addState("Fall", new CharacterFallState());
    _stateMachine->setCurrentState("Idle");

    auto body = PhysicsBody::createBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1));
    this->setPhysicsBody(body);
    this->addChild(_stateMachine);
    body->setRotationEnable(false);


    feetNode = Node::create();
    auto bodyGround = PhysicsBody::createEdgeSegment(Vec2::ZERO, Vec2(10, 0), PhysicsMaterial(1, 0, 1));
    bodyGround->setCategoryBitmask(DefineBitmask::Character);
    bodyGround->setCollisionBitmask(DefineBitmask::NON);
    bodyGround->setContactTestBitmask(DefineBitmask::Wall | DefineBitmask::Box);
    bodyGround->setDynamic(false);
    feetNode->setPhysicsBody(bodyGround);

    auto yGap = 15.0f;
    auto xGap = 6.0f;

    feetNode->setPosition(this->getPositionX() - xGap, this->getPositionY() - yGap);
    this->addChild(feetNode);

    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Character::callbackOnContactBegin, this);
    listener->onContactSeparate = CC_CALLBACK_1(Character::callbackOnContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

    return true;
}

bool Character::loadAnimations()
{
    std::vector<std::string> aniNames;
    aniNames.push_back(_thefile + "-Idle");
    aniNames.push_back(_thefile + "-Run");
    aniNames.push_back(_thefile + "-Jump");
    aniNames.push_back(_thefile + "-Fall");

    for (auto name : aniNames)
    {
        AnimationUtils::loadSpriteFrameCache("Character/", name);
        AnimationUtils::createAnimation(name, 1.0f);
    }

    return true;
}

bool Character::callbackOnContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA != feetNode && nodeB != feetNode) return false;

    auto target = (nodeA == feetNode) ? nodeB : nodeA;
    if ((target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Wall) || (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Box)) {
        isOnGround = true;
        log("1");
    }
    return true;
}

bool Character::callbackOnContactSeparate(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA != feetNode && nodeB != feetNode) return false;

    auto target = (nodeA == feetNode) ? nodeB : nodeA;
    if ((target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Wall) || (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Box)) {
        isOnGround = false;
    }
    return false;
}

