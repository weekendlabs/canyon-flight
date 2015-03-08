#include "cliff.h"
#include "math.h"

USING_NS_CC;

Cliff::Cliff() {
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Cliff::spawnCliff(cocos2d::Layer * layer) {
    CCLOG("SPAWN CLIFF");
    
    // @TODO: Create a texture out of cliff.png
    
    Sprite* leftCliff = Sprite::create("cliff.png");
    
    //@TODO: for changing the height of cliff - still to be optimised
    double random = CCRANDOM_0_1() * 10;
    int flooredValue = floor(random);
    int cliffScale = flooredValue / 2;
    leftCliff->setScaleX(cliffScale);

    leftCliff->setPosition(Point(this->origin.x ,  this->visibleSize.height + leftCliff->getContentSize().height));
    MoveBy* moveBy = MoveBy::create(2, Vec2(this->origin.x , - this->visibleSize.height * 1.2));
    leftCliff->runAction(moveBy);

    //leftCliff->setScaleX(1.5);
    
    layer->addChild(leftCliff);
    
    
//    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize( ) );
//    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize( ) );
//    
//    auto random = CCRANDOM_0_1( );
//    
//    if ( random < LOWER_SCREEN_PIPE_THRESHOLD )
//    {
//        random = LOWER_SCREEN_PIPE_THRESHOLD;
//    }
//    else if ( random > UPPER_SCREEN_PIPE_THRESHOLD )
//    {
//        random = UPPER_SCREEN_PIPE_THRESHOLD;
//    }
//    
//    auto topPipePosition = ( random * visibleSize.height ) + ( topPipe->getContentSize( ).height / 2 );
//    
//    topPipeBody->setDynamic( false );
//    bottomPipeBody->setDynamic( false );
//    
//    topPipe->setPhysicsBody( topPipeBody );
//    bottomPipe->setPhysicsBody( bottomPipeBody );
//    
//    topPipe->setPosition( Point( visibleSize.width + topPipe->getContentSize( ).width + origin.x, topPipePosition ) );
//    bottomPipe->setPosition( Point( topPipe->getPositionX(), topPipePosition - ( Sprite::create( "Ball.png" )->getContentSize( ).height * PIPE_GAP ) - topPipe->getContentSize().height ) );
//    
//    layer->addChild( topPipe );
//    layer->addChild( bottomPipe );
//    
//    auto topPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
//    auto bottomPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
//    
//    topPipe->runAction( topPipeAction );
//    bottomPipe->runAction( bottomPipeAction );
}
