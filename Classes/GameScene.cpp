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

	_character = Character::create("Character");
	_character->setPosition(_position2);
	this->addChild(_character, 2);

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





