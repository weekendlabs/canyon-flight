#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 181, 78, 255))) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->schedule(schedule_selector(GameScene::spawnCliff), 0.40);

   // this->schedule(schedule_selector(GameScene::spawnObstacle), 2.5);
    
    return true;
}

void GameScene::spawnCliff(float dt){
	if(counter == 10){
		counter = 0;
		random = cocos2d::random(10,100);
	}
	else{
		CCLOG("else part counter:%d, random:%d",counter,random);
		++counter;
		if(random % 2 == 0)
			cliff.spawnCliff1(this);
		else
			cliff.spawnCliff2(this);
	}

}

void GameScene::spawnObstacle(float dt) {
    obstacle.spawnObstacle(this);
}
