#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
USING_NS_CC;

class Wall :public DrawNode {
public:
    static Wall* create(std::vector<Vec2> points);

    virtual bool init(std::vector<Vec2> points);
};

#endif // !__WALL_H__
