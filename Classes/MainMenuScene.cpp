#include "MainMenuScene.h"
#include "GameScene.h"
#include "definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK)) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Label * gameTitle = Label::createWithTTF("SineBall", TTF_FONT_FILE, SCALE_960_HEIGHT(100, visibleSize.height));
    gameTitle->setColor(Color3B::WHITE);
    gameTitle->enableOutline(Color4B::BLACK);
    gameTitle->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * (3.0/4.0)));
    this->addChild(gameTitle);
    
    Label * startLabel = Label::createWithTTF("Start", TTF_FONT_FILE, SCALE_960_HEIGHT(80, visibleSize.height));
    MenuItemLabel * startButton = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MainMenuScene::GotoGameScene, this));
    
    Menu * menu = Menu::createWithItem(startButton);
    this->addChild(menu);
    
    
    std::string creditsString;
    
    if (cocos2d::random(0, 10) % 2 == 0) {
        creditsString = "Santhos - Lalith";
    } else {
        creditsString = "Lalith - Santhos";
    }
    
    Label * creditsLabel = Label::createWithTTF(creditsString, TTF_FONT_FILE, SCALE_960_HEIGHT(30, visibleSize.height));
    creditsLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * (0.25 / 4.0)));
    this->addChild(creditsLabel);
    
    Label * highScoreLabel = Label::createWithTTF("High", TTF_FONT_FILE, SCALE_960_HEIGHT(30, visibleSize.height));
    highScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * (1.25 / 4.0)));
    this->addChild(highScoreLabel);
    
    Label * highScoreCountLabel = Label::createWithTTF("100", TTF_FONT_FILE, SCALE_960_HEIGHT(50, visibleSize.height));
    highScoreCountLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * (1.0 / 4.0)));
    this->addChild(highScoreCountLabel);
    
    // If scored is at least 0 then display
    if (~scored) {
        std::string scoreString;

        highScoreLabel->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * (1.25 / 4.0)));
        highScoreCountLabel->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * (1.0 / 4.0)));
        
        char buff[10];
        sprintf(buff, "%d", scored);
        scoreString = buff;
        
        Label * scoreLabel = Label::createWithTTF("Last", TTF_FONT_FILE, SCALE_960_HEIGHT(30, visibleSize.height));
        scoreLabel->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * (1.25 / 4.0)));
        this->addChild(scoreLabel);
        
        Label * scoreCountLabel = Label::createWithTTF(scoreString, TTF_FONT_FILE, SCALE_960_HEIGHT(50, visibleSize.height));
        scoreCountLabel->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * (1.0 / 4.0)));
        this->addChild(scoreCountLabel);
    }
    
    return true;
}

void MainMenuScene::GotoGameScene(cocos2d::Ref * sender) {
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}
