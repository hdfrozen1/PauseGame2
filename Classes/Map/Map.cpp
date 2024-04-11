#include "Map.h"
const std::string GameMap::MapPath = "Map/Demo/";
GameMap* GameMap::create(const std::string& tmxFile)
{
	GameMap* ret = new (std::nothrow) GameMap();
	if (ret->initWithTMXFile(GameMap::MapPath + tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GameMap::initWithTMXFile(const std::string& tmxFile)
{
	if (!TMXTiledMap::initWithTMXFile(tmxFile + ".tmx"))
	{
		log("init GameMap failed!");
		return false;
	}
	
	return true;
}


Point GameMap::convertPosTileMap(Vec2 objectPos) {
	int x = objectPos.x / _tileSize.width;  
	int y = (_mapSize.height * _tileSize.height - objectPos.y) / _tileSize.height;  
	return Point(x, y);
}
