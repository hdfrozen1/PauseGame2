#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
USING_NS_CC;
class GameMap : public TMXTiledMap
{
public:
	static GameMap* create(const std::string& tmxFile);
	bool initWithTMXFile(const std::string& tmxFile);

	Point convertPosTileMap(Vec2 objectPos);

protected:
	TMXLayer* _metaLayer;
public:
	static const std::string MapPath;
};
#endif // !__GAME_MAP_H__