#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Map/Map.h"
#include "Character/Character.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class GameScene :public Scene {
public:
    static Scene* create(std::string mapName);

    virtual bool init(std::string mapName);
protected:
    GameMap* _gameMap;
    Character* _character;
    void onEnter() override;

};

#endif // !__GAME_SCENE_H__
