#include "Wall.h"
#include "DefineBitmask.h"
Wall* Wall::create(std::vector<Vec2> points)
{
    auto newObject = new Wall();
    if (newObject != nullptr && newObject->init(points))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Wall::init(std::vector<Vec2> points)
{
    if (!DrawNode::init()) {
        log("init Wall failed");
        return false;
    }

    auto nodebody = PhysicsBody::createEdgePolygon(points.data(), points.size(),PHYSICSBODY_MATERIAL_DEFAULT,4);
    this->drawPoly(points.data(), points.size(), true, Color4F::WHITE);
    this->setLineWidth(4);
    this->setPhysicsBody(nodebody);
    nodebody->setDynamic(false);

    nodebody->setCategoryBitmask(DefineBitmask::Wall);
    nodebody->setContactTestBitmask(DefineBitmask::Character);
    nodebody->setCollisionBitmask(DefineBitmask::Character);

    return true;
}
