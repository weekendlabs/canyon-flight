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
    
    Sprite * shadowCliff = Sprite::create("cliff.png");
    
    shadowCliff->setScaleX(random + 1.25);
    shadowCliff->setPosition(Point(origin.x, visibleSize.height + leftCliff->getContentSize().height - 15));
    shadowCliff->setColor(Color3B(160, 95, 50));
    
    layer->addChild(shadowCliff, 0);
    

    //right cliff
    Sprite* rightCliff = Sprite::create("cliff.png");
    rightCliff->setScaleX(random + 0.75);
    CCLOG("random value:%f",random);
    int  actualWidthOfLeftCliff = floor((random + 0.75)  * 100);

    CCLOG("screen size:%f",visibleSize.width);
    CCLOG("actul width: %d",actualWidthOfLeftCliff);
    if(actualWidthOfLeftCliff < 0)
        	actualWidthOfLeftCliff = -actualWidthOfLeftCliff;
    CCLOG("modified actul width: %d",actualWidthOfLeftCliff);

    double availableWidth = visibleSize.width - actualWidthOfLeftCliff;
    double rightCliffPosition = visibleSize.width - actualWidthOfLeftCliff ;
    CCLOG("right cliff position:%f",rightCliffPosition);
    if(rightCliffPosition < actualWidthOfLeftCliff){
    	rightCliff->setPosition(Vec2(actualWidthOfLeftCliff+(visibleSize.width - ((rightCliffPosition + actualWidthOfLeftCliff) * 0.5)), leftCliff->getPositionY()));
    	CCLOG("less");
    }
    else{
    	rightCliff->setPosition(Vec2(visibleSize.width - actualWidthOfLeftCliff, leftCliff->getPositionY()));
    	CCLOG("more");
    }
    layer->addChild(rightCliff,1);

    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));
    leftCliff->runAction(moveBy);

    rightCliff->runAction(moveBy->clone());
    shadowCliff->runAction(moveBy->clone());
    
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
