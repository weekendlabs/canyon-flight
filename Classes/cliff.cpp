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
    shouldAdd = !shouldAdd;
    double random = (arc4random_uniform(100) / 75.0) + (shouldAdd?lastScaleValue:-lastScaleValue);
    lastScaleValue = random;
    leftCliff->setScaleX(random + 0.5);
//    leftCliff->setScaleY(0.5);
    CCLOG("%.2f", random);

    leftCliff->setPosition(Point(origin.x, visibleSize.height + leftCliff->getContentSize().height));
    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));
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
