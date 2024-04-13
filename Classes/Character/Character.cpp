#include "Character.h"
#include "AnimationUtils/AnimationUtils.h"
#include "State/CharacterFallState.h"
#include "State/CharacterJumpState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"
#include "DefineBitmask.h"
#include "SettingLayer.h"
class StateMachine;

Character* Character::create(std::string file,float scale)
{
    auto newObject = new Character();
    if (newObject != nullptr && newObject->init(file,scale))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Character::init(std::string file, float scale)
{
    if (!Node::init())
    {
        log("Init Entity failed!");
        return false;
    }
    this->_defaultScale = scale;
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

    body = PhysicsBody::createBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1));
    this->setPhysicsBody(body);
    this->addChild(_stateMachine);
    body->setRotationEnable(false);


    feetNode = Node::create();
    bodyGround = PhysicsBody::createEdgeSegment(Vec2::ZERO, Vec2(14.4, 1), PhysicsMaterial(1, 0, 1));
    bodyGround->setCategoryBitmask(DefineBitmask::Character);
    bodyGround->setCollisionBitmask(DefineBitmask::NON);
    bodyGround->setContactTestBitmask(DefineBitmask::Wall | DefineBitmask::Box);
    bodyGround->setDynamic(false);
    feetNode->setPhysicsBody(bodyGround);

    auto yGap = 16.1f;
    auto xGap = 7.2;

    feetNode->setPosition(this->getPositionX() - xGap, this->getPositionY() - yGap);
    this->addChild(feetNode);
    this->setScale(_defaultScale);

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
        log("can jump");
        if (target->getPhysicsBody()->getCategoryBitmask() == DefineBitmask::Box) {
            isOnBox = true;
            boxNode = target;
            delta = this->getPositionY() - target->getPositionY();
            if (target->getTag() == 123) {
                _isOnCam = true;
            
            }
        }
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
        isOnBox = false;
        log("cant jump");
        if (target->getTag() == 123) {
            _isOnCam = false;
            _defaultScale = this->getScale();
        }
    } 
    return false;
}

void Character::update(float dt)
{
    if (isOnBox && !_isOnCam) {
        this->setPositionY(boxNode->getPositionY() + delta);
    }
}

void Character::onEnter()
{
    Node::onEnter();
    
}

