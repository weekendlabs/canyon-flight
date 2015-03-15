#include "cliff.h"

USING_NS_CC;

#define SCALE_640_WIDTH(x, width) (((x) / 640.0f) * width)
#define SCALE_960_HEIGHT(y, height) (((y) / 960.0f) * height)

Cliff::Cliff() {
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Cliff::spawnCliff(cocos2d::Layer * layer) {
    counter += SCALE_960_HEIGHT(0.075, visibleSize.height);
    double sineValue = sin(counter);
    double gapWidth = SCALE_640_WIDTH(visibleSize.width * 0.5, visibleSize.width);
    
    // ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
    // Sine value ranges from -1 to +1 and width ranges from  gapWidth to visibleSize.width - gapWidth
    double targetX = ((sineValue - -1.0) / (1.0 - -1.0)) * (visibleSize.width - gapWidth) + gapWidth;
    
    CCLOG("Sine Value: %.2f", sineValue);
    CCLOG("Target X  : %.2f", targetX);
    
    // @TODO: Create a texture out of cliff.png
    
    // ------- Left Cliff -------
    double leftCliffWidth = targetX - gapWidth;

    Sprite* leftCliff = Sprite::create("cliff.png");
    
    leftCliff->setScaleX(leftCliffWidth / leftCliff->getContentSize().width);
    leftCliff->setPosition(Point(origin.x + leftCliffWidth * 0.5, visibleSize.height + leftCliff->getContentSize().height));

    layer->addChild(leftCliff, 1);
    
    // ------- Left Cliff Shadow -------
    Sprite* leftCliffShadow = Sprite::create("cliff.png");
    
    leftCliffShadow->setColor(Color3B::BLACK);
    leftCliffShadow->setScaleX(leftCliffWidth / leftCliffShadow->getContentSize().width);
    leftCliffShadow->setPosition(Point(origin.x + SCALE_640_WIDTH(5, visibleSize.width) + leftCliffWidth * 0.5, visibleSize.height + leftCliffShadow->getContentSize().height - SCALE_960_HEIGHT(15, visibleSize.height)));
    
    layer->addChild(leftCliffShadow, 0);
    
    // ------- Right Cliff -------
    double rightCliffWidth = visibleSize.width - (gapWidth + leftCliffWidth); // Whatever is the remaining space
    Sprite* rightCliff = Sprite::create("cliff.png");
    
    rightCliff->setScaleX(rightCliffWidth / rightCliff->getContentSize().width);
    rightCliff->setPosition(Point(visibleSize.width - rightCliffWidth * 0.5, visibleSize.height + rightCliff->getContentSize().height));
    
    layer->addChild(rightCliff, 1);
    
    // ------- Right Cliff Shadow -------
    Sprite* rightCliffShadow = Sprite::create("cliff.png");
    
    rightCliffShadow->setColor(Color3B::BLACK);
    rightCliffShadow->setScaleX(rightCliffWidth / rightCliffShadow->getContentSize().width);
    rightCliffShadow->setPosition(Point(visibleSize.width + SCALE_640_WIDTH(-5, visibleSize.width) - rightCliffWidth * 0.5, visibleSize.height + rightCliffShadow->getContentSize().height - SCALE_960_HEIGHT(15, visibleSize.height)));
    
    layer->addChild(rightCliffShadow, 0);
    
    // ------ Moving the cliffs and shadows to the bottom ------
    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

    leftCliff->runAction(moveBy);
    leftCliffShadow->runAction(moveBy->clone());
    rightCliff->runAction(moveBy->clone());
    rightCliffShadow->runAction(moveBy->clone());
}
