#include "cliff.h"

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
    double random = (cocos2d::random(0, 100) / 75.0) + (shouldAdd?lastScaleValue:-lastScaleValue);
    lastScaleValue = random;

    leftCliff->setScaleX(random + 0.75);
    leftCliff->setPosition(Point(origin.x, visibleSize.height + leftCliff->getContentSize().height));

    layer->addChild(leftCliff, 1);
    
    Sprite * leftCliffShadow = Sprite::create("cliff.png");
    
    leftCliffShadow->setScaleX(random + 1.25);
    leftCliffShadow->setPosition(Point(origin.x, visibleSize.height + leftCliff->getContentSize().height - 15));
    leftCliffShadow->setColor(Color3B(160, 95, 50));
    
    layer->addChild(leftCliffShadow, 0);

    //right cliff
    Sprite* rightCliff = Sprite::create("cliff.png");
    rightCliff->setScaleX(random + 0.75);
    double actualWidthOfLeftCliff = (random + 0.75) * leftCliff->getContentSize().width;

    double rightCliffX = visibleSize.width - actualWidthOfLeftCliff * 0.5;
    
    rightCliff->setPosition(Point(rightCliffX + actualWidthOfLeftCliff * 0.5, leftCliff->getPositionY()));
   
    layer->addChild(rightCliff, 1);

    Sprite * rightCliffShadow = Sprite::create("cliff.png");
    
    rightCliffShadow->setScaleX(random + 1.25);
    rightCliffShadow->setPosition(Point(rightCliff->getPositionX() + 35, visibleSize.height + rightCliff->getContentSize().height - 15));
    rightCliffShadow->setColor(Color3B(160, 95, 50));
    
    layer->addChild(rightCliffShadow, 0);
    
    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

    leftCliff->runAction(moveBy);
    rightCliff->runAction(moveBy->clone());
    leftCliffShadow->runAction(moveBy->clone());
    rightCliffShadow->runAction(moveBy->clone());
    
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
