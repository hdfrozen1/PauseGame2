#include "GameScene.h"
#include "Wall/Wall.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"
#include "DefineBitmask.h"
#include "SettingLayer.h"
Scene* GameScene::create(std::string mapName)
{
	auto newObject = new GameScene();
	if (newObject != nullptr && newObject->init(mapName))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool GameScene::init(std::string mapName)
{
	if(!Scene::initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
	this->getPhysicsWorld()->setSpeed(5);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// Map
	_gameMap = GameMap::create(mapName);
	_gameMap->setTag(99);

	TMXObjectGroup* MapPoint = _gameMap->getObjectGroup("Ground");
	auto mappoints = MapPoint->getObjects();
	std::vector<Vec2> points;
	for (auto point : mappoints) {
		ValueMap puppleSpawnPoint = point.asValueMap();
		Vec2 _position;
		_position.x = puppleSpawnPoint["x"].asFloat();
		_position.y = puppleSpawnPoint["y"].asFloat();
		points.push_back(_position);
	}

	auto wall = Wall::create(points);
	//wall->setScale(0.5);

	Vec2 wallpos = wall->getPosition();
	log("wall x : %f", wallpos.x);
	log("wall y : %f", wallpos.y);

	this->addChild(wall);


	TMXObjectGroup* spawnPoint = _gameMap->getObjectGroup("Character");
	ValueMap charPoint = spawnPoint->getObject("SpawnPoint");
	Vec2 _position2;
	_position2.x = charPoint["x"].asFloat();
	_position2.y = charPoint["y"].asFloat();


	/*auto character = Sprite::create("CloseNormal.png");
	auto charbody = PhysicsBody::createCircle(character->getContentSize().width / 2,PhysicsMaterial(1, 0, 0));
	character->setPosition(_position2);
	this->addChild(character);
	character->setPhysicsBody(charbody);
	charbody->applyImpulse(Vec2(0, 99999));
	log("%d", charbody->getMass());*/

	_character = Character::create("Character");
	_character->setPosition(_position2);
	this->addChild(_character, 2);
	
	/*auto slider = ui::Slider::create();
	slider->loadBarTexture("Slider.png");
	slider->loadSlidBallTextureNormal("Gravity.png");
	slider->loadSlidBallTexturePressed("Gravity.png");
	slider->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(slider);
	slider->setPercent(50);
	slider->setRotation(-90);

	gravitynode = Node::create();
	auto gravitybody2 = PhysicsBody::createBox(slider->getSlidBallNormalRenderer()->getContentSize(),PhysicsMaterial(1,0,1));
	gravitynode->setPhysicsBody(gravitybody2);
	gravitynode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(gravitynode);
	gravitybody2->setGravityEnable(false);
	gravitybody2->setDynamic(false);
	gravitybody2->setCategoryBitmask(DefineBitmask::Box);
	gravitybody2->setCollisionBitmask(DefineBitmask::Character);
	gravitybody2->setContactTestBitmask(DefineBitmask::Character);
	

	slidersize = slider->getContentSize();

	slider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
			ui::Slider* slider2 = dynamic_cast<ui::Slider*>(sender);
			if (slider2) {
				int percent = slider2->getPercent();
				log("percent : %d", percent);
				
				float lenght = slidersize.width / 100 * percent;
				log("lenght : %f", slidersize.height);
				float the_x = 480 - slidersize.width / 2 + lenght;
				gravitynode->setPosition(Vec2(640, the_x));
			}
		}
		});*/

	/*auto camera = this->getDefaultCamera();
	Vec3 campos = camera->getPosition3D();
	Vec3 newcampos = Vec3(640, 480, 1200);
	camera->setPosition3D(newcampos);


	float scale = newcampos.z / campos.z;
	auto close = Sprite::create("CloseSelected.png");
	close->setPosition(Vec2(500, 500));
	close->setScale(scale);
	this->addChild(close);

	auto closebody = PhysicsBody::createBox(close->getContentSize(),PHYSICSBODY_MATERIAL_DEFAULT,Vec2(0.5,0.5));
	close->setPhysicsBody(closebody);
	closebody->setCategoryBitmask(DefineBitmask::Wall);
	closebody->setContactTestBitmask(DefineBitmask::Character);
	closebody->setCollisionBitmask(DefineBitmask::Character);
	closebody->setGravityEnable(false);
	closebody->setDynamic(false);*/

	auto setting = SettingLayer::create();
	this->addChild(setting);
	

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();
	
	this->addChild(KeyboardInput::getInstance());
}
