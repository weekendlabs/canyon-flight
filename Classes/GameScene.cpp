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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundLayer = LayerColor::create(Color4B(255, 181, 78, 255), visibleSize.width, visibleSize.height);
    backgroundLayer->setPosition(Point(0, 0));
    this->addChild(backgroundLayer);
    
    this->schedule(schedule_selector(GameScene::spawnCliff), 0.001);

    

    return true;
}

void GameScene::spawnCliff(float dt){
	cliff.spawnCliff(this);
}
