#include "cliff.h"

USING_NS_CC;

#define SCALE_640_WIDTH(x, width) (((x) / 640.0f) * width)
#define SCALE_960_HEIGHT(y, height) (((y) / 960.0f) * height)

Cliff::Cliff() {
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Cliff::spawnCliff(cocos2d::Layer * layer) {
    // @TODO: Create a texture out of cliff.png
    double targetWidth = cocos2d::random(SCALE_640_WIDTH(75, visibleSize.width), SCALE_640_WIDTH(125, visibleSize.width));
    
    // ------- Left Cliff -------
    Sprite* leftCliff = Sprite::create("cliff.png");
    
    leftCliff->setScaleX( targetWidth / leftCliff->getContentSize().width);
    leftCliff->setPosition(Point(origin.x + targetWidth * 0.5, visibleSize.height + leftCliff->getContentSize().height));

    layer->addChild(leftCliff, 1);
    
    // ------- Left Cliff Shadow -------
    Sprite* leftCliffShadow = Sprite::create("cliff.png");
    
    leftCliffShadow->setColor(Color3B::BLACK);
    leftCliffShadow->setScaleX(targetWidth / leftCliffShadow->getContentSize().width);
    leftCliffShadow->setPosition(Point(origin.x + SCALE_640_WIDTH(5, visibleSize.width) + targetWidth * 0.5, visibleSize.height + leftCliffShadow->getContentSize().height - SCALE_960_HEIGHT(15, visibleSize.height)));
    
    layer->addChild(leftCliffShadow, 0);
    
    // ------- Right Cliff -------
    Sprite* rightCliff = Sprite::create("cliff.png");
    
    rightCliff->setScaleX( targetWidth / rightCliff->getContentSize().width);
    rightCliff->setPosition(Point(visibleSize.width - targetWidth * 0.5, visibleSize.height + rightCliff->getContentSize().height));
    
    layer->addChild(rightCliff, 1);
    
    // ------- Right Cliff Shadow -------
    Sprite* rightCliffShadow = Sprite::create("cliff.png");
    
    rightCliffShadow->setColor(Color3B::BLACK);
    rightCliffShadow->setScaleX(targetWidth / rightCliffShadow->getContentSize().width);
    rightCliffShadow->setPosition(Point(visibleSize.width + SCALE_640_WIDTH(-5, visibleSize.width) - targetWidth * 0.5, visibleSize.height + rightCliffShadow->getContentSize().height - SCALE_960_HEIGHT(15, visibleSize.height)));
    
    layer->addChild(rightCliffShadow, 0);
    
    // ------ Moving the cliffs and shadows to the bottom ------
    MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

    leftCliff->runAction(moveBy);
    leftCliffShadow->runAction(moveBy->clone());
    rightCliff->runAction(moveBy->clone());
    rightCliffShadow->runAction(moveBy->clone());
}
