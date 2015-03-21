#include "GameScene.h"
#include "definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    
    PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(visibleSize,
      			PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(CLIFF_COLLISION_MASK);
    edgeBody->setContactTestBitmask(true);
    Node* edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    this->schedule(schedule_selector(GameScene::spawnCliff), 0.325 * 0.5);

    double circleRadius = (visibleSize.width * 0.05) / 2;
    circle = Sprite::create("circle.png");
    circle->setPosition(Vec2((visibleSize.width - circleRadius) * 0.5, (visibleSize.height - circleRadius) * 0.5));
    circle->setScale((circleRadius * 2) / circle->getContentSize().width, (circleRadius * 2) / circle->getContentSize().height);
    
    PhysicsBody* circleBody = PhysicsBody::createCircle(circleRadius);
    circleBody->setCollisionBitmask(CIRCLE_COLLISION_MASK);
    circleBody->setContactTestBitmask(true);
    
    circle->setPhysicsBody(circleBody);
    
    this->addChild(circle, 1);

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

    this->addChild(scoreLabel,100000);

    return true;
}

void GameScene::spawnCliff(float dt){
	cliff.spawnCliff(this);
	score = score + 1;
	 __String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel->setString(tempScore->getCString());
}


void GameScene::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event){
//	circle->setPosition(circle->getPositionX() + acc->x, circle->getPositionY() + acc->y);
    // This will give us a value in the closure -1.0 <= x <= +1.0
    
    // ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
    double moveByX = ((acc->x - -1.0) / (1.0 - -1.0)) * (2.5 - -2.5) + -2.5;
    double moveByY = ((acc->y - -1.0) / (1.0 - -1.0)) * (2.5 - -2.5) + -2.5;
    
//    MoveBy * moveByAction = MoveBy::create(0.01, Vec2(moveByX, 0));
//    circle->runAction(moveByAction);
    circle->setPosition(circle->getPositionX() + moveByX, circle->getPositionY() + moveByY);
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

