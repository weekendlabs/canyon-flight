#ifndef __canyon_flight__obstacle__
#define __canyon_flight__obstacle__

#include "cocos2d.h"

class Obstacle
{
public:
    Obstacle();
    
    void spawnObstacle(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif /* defined(__canyon_flight__obstacle__) */
