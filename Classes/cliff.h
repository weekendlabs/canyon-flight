#ifndef __canyon_flight__cliff__
#define __canyon_flight__cliff__

#include "cocos2d.h"
#include "definitions.h"

class Cliff
{
public:
    Cliff();
    
    void spawnCliff(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Texture2D * cliffTexture;
    
    double counter = 0;
    double step = 25.0;
    double velocity = 0;
    double counterAcceleration = 0.01;
};

#endif /* defined(__canyon_flight__cliff__) */
