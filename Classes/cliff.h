#ifndef __canyon_flight__cliff__
#define __canyon_flight__cliff__

#include "cocos2d.h"

class Cliff
{
public:
    Cliff();
    
    void spawnCliff1(cocos2d::Layer * layer);
    
    void spawnCliff2(cocos2d::Layer * layer);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif /* defined(__canyon_flight__cliff__) */
