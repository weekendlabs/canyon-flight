#include "HelpScene.h"
#include "GameScene.h"
#include "definitions.h"
#include "AdmobHelper.h"
#include "MainMenuScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iOSHelper.h"
#endif

USING_NS_CC;

bool shouldGotoGameScene;

Scene* HelpScene::createScene(bool gotoGameScene)
{
    
    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    shouldGotoGameScene = gotoGameScene;

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
    
    // ---------------- Rotating Phone Image -------------------
    Sprite* phoneSprite;
    
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		phoneSprite = Sprite::create("phone.png");
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		phoneSprite = Sprite::create("iphone.png");
	#endif

    phoneSprite->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    this->addChild(phoneSprite,1000);
    RotateTo* rotateRight = RotateTo::create(1,Vec3(0, 0, 15));
    RotateTo* rotateLeft = RotateTo::create(1,Vec3(0, 0, -15));

    RepeatForever* repeatPhone = RepeatForever::create(Sequence::create(rotateLeft, rotateRight, NULL));
    phoneSprite->runAction(repeatPhone);
    
    // ---------------- Swinging Circle -------------------
    double circleRadius = (visibleSize.width * SCALE_640_WIDTH(0.05, visibleSize.width)) / 2;
    Sprite * circle = Sprite::create("circle.png");
    this->addChild(circle);
    circle->setPosition(Vec2((visibleSize.width - circleRadius) * 0.5, (visibleSize.height - circleRadius) * 0.5));
    circle->setScale((circleRadius * 2) / circle->getContentSize().width, (circleRadius * 2) / circle->getContentSize().height);
    circle->setColor(Color3B::BLACK);
    
    MoveTo* moveToLeft = MoveTo::create(1, Vec2((visibleSize.width * 0.5) - 30, visibleSize.height * 0.5));
    MoveTo* moveToRight = MoveTo::create(1, Vec2((visibleSize.width * 0.5) + 30, visibleSize.height * 0.5));
    RepeatForever* repeatCircle = RepeatForever::create(Sequence::create(moveToLeft, moveToRight, NULL));
    circle->runAction(repeatCircle);
    
    // ---------------- Labels -------------------
    Label * instructionLabel = Label::createWithTTF("        Tilt to move the ball\nKeep ball inside white space", TTF_FONT_FILE, SCALE_960_HEIGHT(30, visibleSize.height));
	instructionLabel->setColor(Color3B::BLACK);
	instructionLabel->enableOutline(Color4B::WHITE);
	instructionLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.9));
	this->addChild(instructionLabel);

	Label * dismissLabel = Label::createWithTTF("Tap to dismiss", TTF_FONT_FILE, SCALE_960_HEIGHT(25, visibleSize.height));
	dismissLabel->setColor(Color3B::BLACK);
	dismissLabel->enableOutline(Color4B::WHITE);
	dismissLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.1));
	this->addChild(dismissLabel);

    // ------------- Touch Listeners --------------
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
    Scene * scene = nullptr;
    if (shouldGotoGameScene) {
        scene = GameScene::createScene();
    } else {
        scene = MainMenuScene::createScene();
    }
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
