#include "GameScene.h"
#include "definitions.h"
#include "MainMenuScene.h"
#include "AdmobHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iOSHelper.h"
#endif

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
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
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    cliffSpawnRate = SCALE_960_HEIGHT(0.15, visibleSize.height);
    
    PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(visibleSize,
      			PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(CLIFF_COLLISION_MASK);
    edgeBody->setContactTestBitmask(true);
    Node* edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    double circleRadius = (visibleSize.width * 0.05) / 2;
    circle = Sprite::create("circle.png");
    circle->setPosition(Vec2((visibleSize.width - circleRadius) * 0.5, (visibleSize.height - circleRadius) * 0.5));
    circle->setScale((circleRadius * 2) / circle->getContentSize().width, (circleRadius * 2) / circle->getContentSize().height);
    
    PhysicsBody* circleBody = PhysicsBody::createCircle(circleRadius);
    circleBody->setCollisionBitmask(CIRCLE_COLLISION_MASK);
    circleBody->setContactTestBitmask(true);
    
    circle->setPhysicsBody(circleBody);
    
    this->addChild(circle, 10005);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

    Device::setAccelerometerEnabled(true);
    EventListenerAcceleration* listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    //adding score label
    __String *tempScore = __String::createWithFormat("%i",score);
    //std::string tempScore = score + "";
    scoreLabel = Label::createWithTTF(tempScore->getCString(), TTF_FONT_FILE, visibleSize.height * SCORE_LABEL_SCALE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->enableOutline(Color4B::BLACK,10);
    scoreLabel->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.75 + origin.y));

    this->addChild(scoreLabel, 1001);
    
    scheduleUpdate();
    
    //------ admob ads -------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AdmobHelper::showAd();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    iOSHelper::showAdmobBanner();
#endif


    this->setKeypadEnabled(true);
	this->setKeyboardEnabled(true);
	EventListenerKeyboard *keyboardEventListener = EventListenerKeyboard::create();
	keyboardEventListener->setEnabled(true);
	keyboardEventListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardEventListener,this);

    return true;
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACK){
		CCLOG("You pressed back button from game scene");
		auto * scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	}
}

void GameScene::spawnCliff() {
    if (deltaAccum >= cliffSpawnRate) {
        cliff.spawnCliff(this);
        score = score + 1;
        __String *tempScore = __String::createWithFormat("%i", score);
        scoreLabel->setString(tempScore->getCString());
        
        deltaAccum = 0;
    }
}

void GameScene::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event){
    float accelerationXFactor = SCALE_640_WIDTH(7.5, visibleSize.width);
    
    if ((circleVelocity.x < 0 && acc->x > 0) || (circleVelocity.x > 0 && acc->x < 0)) {
        circleVelocity.x = acc->x * accelerationXFactor;
    } else {
        circleVelocity.x += acc->x * accelerationXFactor;
    }
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((CLIFF_COLLISION_MASK == a->getCollisionBitmask() && CIRCLE_COLLISION_MASK == b->getCollisionBitmask()) ||
        (CIRCLE_COLLISION_MASK == a->getCollisionBitmask() && CLIFF_COLLISION_MASK == b->getCollisionBitmask())) {
        auto * scene = MainMenuScene::createScene(score);
        
        Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	}

	return true;
}

void GameScene::update(float delta) {
    Vec2 pos = circle->getPosition();
    
    pos.x += circleVelocity.x * delta;
    
    circle->setPosition(pos);
    
    deltaAccum += delta;
    spawnCliff();
}
