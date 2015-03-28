#include "obstacle.h"
#include "definitions.h"

USING_NS_CC;

Obstacle::Obstacle() {
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Obstacle::spawnObstacle(cocos2d::Layer * layer) {
    
    DrawNode * obstacle = DrawNode::create();
    
    auto random = cocos2d::random(0, 100);
    
    if (random % 2 == 0) {
        obstacle->drawDot(Vec2(visibleSize.width * 0.5, visibleSize.height + 100), 50, Color4F::BLACK);
    } else {
        obstacle->drawTriangle(
           Vec2(visibleSize.width * 0.5 - 50, visibleSize.height),
           Vec2(visibleSize.width * 0.5, visibleSize.height + 50),
           Vec2(visibleSize.width * 0.5 + 50, visibleSize.height),
           Color4F::WHITE);
    }
    
    layer->addChild(obstacle);
    
    // ------ Moving the cliffs and shadows to the bottom ------
    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

    obstacle->runAction(moveBy);
}
