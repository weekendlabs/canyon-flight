#include "cliff.h"
#include "definitions.h"

USING_NS_CC;

Cliff::Cliff() {
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Cliff::spawnCliff(cocos2d::Layer * layer) {
    counter += SCALE_960_HEIGHT(0.075, visibleSize.height);
    double sineValue = sin(counter);
    
    // |-- targetX -|-gw--|- remaining -| = visibleWidth
    // |-Left Cliff-|-Gap-|-Right Cliff-| = visibleWidth
    
    // visibleWidth * 0.25 <= gapWidth <= visibleWidth * 0.5
    const double MAX_GAP_WIDTH = visibleSize.width * 0.5;
    double gapWidth = MAX_GAP_WIDTH;
    
    // ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
    // Sine value ranges from -1 to +1 and width ranges from  gapWidth to visibleSize.width - gapWidth
    // -1.0 <= x <= +1.0 ---> gapWidth <= targetX <= (visibleWidth - gapWidth)
    double targetX = ((sineValue - -1.0) / (1.0 - -1.0)) * (visibleSize.width - gapWidth) + gapWidth;

    // ------- Left Cliff -------
    double leftCliffWidth = targetX - gapWidth;
    double cliffHeight = SCALE_960_HEIGHT(100, visibleSize.height);

    Sprite* leftCliff = Sprite::create("cliff.png");
    
    leftCliff->setScaleX(leftCliffWidth / leftCliff->getContentSize().width);
    leftCliff->setScaleY(cliffHeight / leftCliff->getContentSize().height);
    leftCliff->setColor(Color3B::BLACK);
    leftCliff->setPosition(Point(origin.x + leftCliffWidth * 0.5, visibleSize.height + leftCliff->getContentSize().height));

    //Adding physics body
    PhysicsBody* leftCliffBody = PhysicsBody::createBox(Size(leftCliffWidth, cliffHeight));
    leftCliffBody->setDynamic(false);
    leftCliffBody->setCollisionBitmask(CLIFF_COLLISION_MASK);
    leftCliffBody->setContactTestBitmask(true);
    leftCliff->setPhysicsBody(leftCliffBody);
 
    layer->addChild(leftCliff, 1);

    // ------- Right Cliff -------
    double rightCliffWidth = visibleSize.width - (gapWidth + leftCliffWidth); // Whatever is the remaining space
    Sprite* rightCliff = Sprite::create("cliff.png");
    
    rightCliff->setScaleX(rightCliffWidth / rightCliff->getContentSize().width);
    rightCliff->setScaleY(cliffHeight / rightCliff->getContentSize().height);
    rightCliff->setColor(Color3B::BLACK);
    rightCliff->setPosition(Point(visibleSize.width - rightCliffWidth * 0.5, visibleSize.height + rightCliff->getContentSize().height));
    
    //Adding physics body
    PhysicsBody* rightCliffBody = PhysicsBody::createBox(Size(rightCliffWidth, cliffHeight));
    rightCliffBody->setDynamic(false);
    rightCliffBody->setCollisionBitmask(CLIFF_COLLISION_MASK);
    rightCliffBody->setContactTestBitmask(true);
    rightCliff->setPhysicsBody(rightCliffBody);
 
    layer->addChild(rightCliff, 1);

    // ------ Moving the cliffs and shadows to the bottom ------
    MoveBy* moveBy = MoveBy::create(SCALE_960_HEIGHT(2.5, visibleSize.height), Vec2(0, -(visibleSize.height + cliffHeight * 2)));
    RemoveSelf* remove = RemoveSelf::create();

    leftCliff->runAction(Sequence::create(moveBy, remove, NULL));
    rightCliff->runAction(Sequence::create(moveBy->clone(), remove->clone(), NULL));
}
