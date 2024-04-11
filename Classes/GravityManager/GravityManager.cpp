#include "GravityManager.h"
#include "cocos2d.h"
USING_NS_CC;

GravityManager* GravityManager::_instance;
GravityManager* GravityManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new GravityManager();
    }
    return _instance;
}

void GravityManager::setGravityValue(float newVolume)
{
    _gravityvalue = newVolume;
    Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0, _gravityvalue));
}
