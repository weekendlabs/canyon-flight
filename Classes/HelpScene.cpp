#include "HelpScene.h"
#include "GameScene.h"
#include "definitions.h"
#include "AdmobHelper.h"
#include "MainMenuScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iOSHelper.h"
#endif

USING_NS_CC;

Scene* HelpScene::createScene()
{
    
    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Sprite* phoneSprite;
    

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		phoneSprite = Sprite::create("phone.png");
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		phoneSprite = Sprite::create("iphone.png");
	#endif

    phoneSprite->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    this->addChild(phoneSprite,1000);
    RotateTo* rotateRight = RotateTo::create(2,Vec3(0,30,0));
    RotateTo* rotateLeft = RotateTo::create(2,Vec3(0,-30,0));

    RepeatForever* repeat = RepeatForever::create(Sequence::create(rotateLeft,rotateRight,NULL));
    phoneSprite->runAction(repeat);
    
    Label * instructionLabel = Label::createWithTTF("Tilt the Phone to Play !!", TTF_FONT_FILE, SCALE_960_HEIGHT(30, visibleSize.height));
	instructionLabel->setColor(Color3B::BLACK);
	instructionLabel->enableOutline(Color4B::WHITE);
	instructionLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.9));
	this->addChild(instructionLabel);


	Label * proceedLabel = Label::createWithTTF("Tap anywhere to proceed..", TTF_FONT_FILE, SCALE_960_HEIGHT(30, visibleSize.height));
	proceedLabel->setColor(Color3B::BLACK);
	proceedLabel->enableOutline(Color4B::WHITE);
	proceedLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.1));
	this->addChild(proceedLabel);


    EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(HelpScene::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

    this->setKeypadEnabled(true);
    this->setKeyboardEnabled(true);
    EventListenerKeyboard *keyboardEventListener = EventListenerKeyboard::create();
    keyboardEventListener->setEnabled(true);
    keyboardEventListener->onKeyReleased = CC_CALLBACK_2(HelpScene::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardEventListener,this);

    return true;
}

bool HelpScene::onTouchBegan(Touch* touch, Event* event){
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}

void HelpScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACK){
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	}
}


void HelpScene::GotoGameScene(cocos2d::Ref * sender) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}
