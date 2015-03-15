#include "cliff.h"
#include "definitions.h"

USING_NS_CC;

Cliff::Cliff() {
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Cliff::spawnCliff(cocos2d::Layer * layer) {
//    double counterInc = cocos2d::random(SCALE_640_WIDTH(0.075, visibleSize.width), SCALE_640_WIDTH(0.15, visibleSize.width));
    counter += SCALE_960_HEIGHT(0.075, visibleSize.height);
    double sineValue = sin(counter);
    counter += sin(counter * 0.01);
    
    // |-- targetX -|-gw--|- remaining -| = visibleWidth
    // |-Left Cliff-|-Gap-|-Right Cliff-| = visibleWidth
    
    // visibleWidth * 0.25 <= gapWidth <= visibleWidth * 0.5
    const double MAX_GAP_WIDTH = SCALE_640_WIDTH(visibleSize.width * 0.5, visibleSize.width);
    const double MIN_GAP_WIDTH = SCALE_640_WIDTH(visibleSize.width * 0.25, visibleSize.width);
//    double gapWidth = ((sineValue - -1.0) / (1.0 - -1.0)) * (MAX_GAP_WIDTH - MIN_GAP_WIDTH) + MIN_GAP_WIDTH;
    double gapWidth = MAX_GAP_WIDTH;
    
    // ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
    // Sine value ranges from -1 to +1 and width ranges from  gapWidth to visibleSize.width - gapWidth
    // -1.0 <= x <= +1.0 ---> gapWidth <= targetX <= (visibleWidth - gapWidth)
    double targetX = ((sineValue - -1.0) / (1.0 - -1.0)) * (visibleSize.width - gapWidth) + gapWidth;
    
    CCLOG("Counter value: %.2f", counter);
    CCLOG("Sine Value: %.2f", sineValue);
    CCLOG("Target X  : %.2f", targetX);
    
    // @TODO: Create a texture out of cliff.png
    
    // ------- Left Cliff -------
    double leftCliffWidth = targetX - gapWidth;

    Sprite* leftCliff = Sprite::create("cliff.png");
    
    leftCliff->setScaleX(leftCliffWidth / leftCliff->getContentSize().width);
    leftCliff->setColor(Color3B::BLACK);
    leftCliff->setPosition(Point(origin.x + leftCliffWidth * 0.5, visibleSize.height + leftCliff->getContentSize().height));

    layer->addChild(leftCliff, 1);

    // ------- Right Cliff -------
    double rightCliffWidth = visibleSize.width - (gapWidth + leftCliffWidth); // Whatever is the remaining space
    Sprite* rightCliff = Sprite::create("cliff.png");
    
    rightCliff->setScaleX(rightCliffWidth / rightCliff->getContentSize().width);
    rightCliff->setColor(Color3B::BLACK);
    rightCliff->setPosition(Point(visibleSize.width - rightCliffWidth * 0.5, visibleSize.height + rightCliff->getContentSize().height));
    
    layer->addChild(rightCliff, 1);
    
    // ------ Moving the cliffs and shadows to the bottom ------
    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

    leftCliff->runAction(moveBy);
    rightCliff->runAction(moveBy->clone());
}
