#include "SettingLayer.h"
#include "DefineBitmask.h"
Layer* SettingLayer::create()
{
    auto newObject = new SettingLayer();
    if (newObject != nullptr && newObject->init())
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool SettingLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    distance = visibleSize.width / 4;
    y_pos = visibleSize.height / 2;

    _graSlider = ui::Slider::create();
    _graSlider->loadBarTexture("Slider.png");
    _graSlider->loadSlidBallTextureNormal("Gravity.png");
    _graSlider->loadSlidBallTexturePressed("Gravity.png");
    _graSlider->setPosition(Vec2(distance, y_pos));
    _graSlider->setPercent(50);
    _graSlider->setRotation(-90);
    this->addChild(_graSlider);
    _graSliderSize = _graSlider->getContentSize();

    _graNode = Node::create();
    auto gravitybody2 = PhysicsBody::createBox(_graSlider->getSlidBallNormalRenderer()->getContentSize(), PhysicsMaterial(1, 0, 1));
    _graNode->setPhysicsBody(gravitybody2);
    _graNode->setPosition(Vec2(distance, y_pos));
    this->addChild(_graNode);
    gravitybody2->setGravityEnable(false);
    gravitybody2->setDynamic(false);
    gravitybody2->setCategoryBitmask(DefineBitmask::Box);
    gravitybody2->setCollisionBitmask(DefineBitmask::Character);
    gravitybody2->setContactTestBitmask(DefineBitmask::Character );

    _graSlider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            ui::Slider* slider2 = dynamic_cast<ui::Slider*>(sender);
            if (slider2) {
                int percent = slider2->getPercent();
                log("percent : %d", percent);

                float lenght = _graSliderSize.width / 100 * percent;
                log("lenght : %f", _graSliderSize.height);
                float the_x =y_pos - _graSliderSize.width / 2 + lenght;
                _graNode->setPosition(Vec2(distance, the_x));

                float y_gravity = clampf((float)percent * (-1), -98.0f, -12.0f);
                Director::getInstance()->getRunningScene()->getPhysicsWorld()->setGravity(Vec2(0, y_gravity));
            }
        }
        });


    _camSlider = ui::Slider::create();
    _camSlider->loadBarTexture("Slider.png");
    _camSlider->loadSlidBallTextureNormal("Camera.png");
    _camSlider->loadSlidBallTexturePressed("Camera.png");
    _camSlider->setPosition(Vec2(distance*2, y_pos));
    _camSlider->setPercent(50);
    _camSlider->setRotation(-90);
    this->addChild(_camSlider);
    _camSliderSize = _camSlider->getContentSize();

    _camNode = Node::create();
    auto gravitybody3 = PhysicsBody::createBox(_camSlider->getSlidBallNormalRenderer()->getContentSize(), PhysicsMaterial(1, 0, 1));
    _camNode->setPhysicsBody(gravitybody3);
    _camNode->setPosition(Vec2(distance * 2, y_pos));
    this->addChild(_camNode);
    gravitybody3->setGravityEnable(false);
    gravitybody3->setDynamic(false);
    gravitybody3->setCategoryBitmask(DefineBitmask::Box);
   
    gravitybody3->setContactTestBitmask(DefineBitmask::Character );
 gravitybody3->setCollisionBitmask(DefineBitmask::Character);
    _camSlider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            ui::Slider* slider2 = dynamic_cast<ui::Slider*>(sender);
            if (slider2) {
                int percent = slider2->getPercent();
                log("percent : %d", percent);

                float lenght = _camSliderSize.width / 100 * percent;
                log("lenght : %f", _camSliderSize.height);
                float the_x = y_pos - _camSliderSize.width / 2 + lenght;
                _camNode->setPosition(Vec2(distance*2, the_x));

            }
        }
        });


    _spdSlider = ui::Slider::create();
    _spdSlider->loadBarTexture("Slider.png");
    _spdSlider->loadSlidBallTextureNormal("Speed.png");
    _spdSlider->loadSlidBallTexturePressed("Speed.png");
    _spdSlider->setPosition(Vec2(distance * 3, y_pos));
    _spdSlider->setPercent(50);
    _spdSlider->setRotation(-90);
    this->addChild(_spdSlider);
    _spdSliderSize = _spdSlider->getContentSize();

    _spdNode = Node::create();
    auto gravitybody4 = PhysicsBody::createBox(_spdSlider->getSlidBallNormalRenderer()->getContentSize(), PhysicsMaterial(1, 0, 1));
    _spdNode->setPhysicsBody(gravitybody4);
    _spdNode->setPosition(Vec2(distance * 3, y_pos));
    this->addChild(_spdNode);
    gravitybody4->setGravityEnable(false);
    gravitybody4->setDynamic(false);
    gravitybody4->setCategoryBitmask(DefineBitmask::Box);
    
    gravitybody4->setContactTestBitmask(DefineBitmask::Character );
gravitybody4->setCollisionBitmask(DefineBitmask::Character);
    _spdSlider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            ui::Slider* slider2 = dynamic_cast<ui::Slider*>(sender);
            if (slider2) {
                int percent = slider2->getPercent();
                log("percent : %d", percent);

                float lenght = _spdSliderSize.width / 100 * percent;
                log("lenght : %f", _spdSliderSize.height);
                float the_x = y_pos - _spdSliderSize.width / 2 + lenght;
                _spdNode->setPosition(Vec2(distance * 3, the_x));

                float y_speed = clampf((float)percent / 10, 1.0f, 9.0f);
                Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(y_speed);
            }
        }
        });


    return true;
}
