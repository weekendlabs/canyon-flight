#include "GameScene.h"
#include "definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    
    this->schedule(schedule_selector(GameScene::spawnCliff), 0.50);

    obstacle = DrawNode::create();
    obstacle->drawDot(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5), visibleSize.width * 0.05, Color4F::BLACK);
    PhysicsBody* obstacleBody = PhysicsBody::createCircle((visibleSize.width * 0.05 )/ 2);
    obstacleBody->setDynamic(false);
    obstacleBody->setCollisionBitmask(BALL_COLLISION_MASK);
    obstacleBody->setContactTestBitmask(true);
    obstacle->setPhysicsBody(obstacleBody);
    this->addChild(obstacle, 1);

    EventListenerPhysicsContact* contactListener =EventListenerPhysicsContact::create();
    contactListener->onContactBegin =CC_CALLBACK_1(GameScene::onContactBegin,this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

    Device::setAccelerometerEnabled(true);
    EventListenerAcceleration* listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

void GameScene::spawnCliff(float dt){
	cliff.spawnCliff(this);
}


void GameScene::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event){
	obstacle->setPosition(obstacle->getPositionX() + acc->x, obstacle->getPositionY() + acc->y);
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((CLIFF_COLLISION_MASK == a->getCollisionBitmask()
			&& BALL_COLLISION_MASK == b->getCollisionBitmask())
			|| (BALL_COLLISION_MASK == b->getCollisionBitmask()
					&& CLIFF_COLLISION_MASK == a->getCollisionBitmask())) {
		//creation of game over label
		CCLOG("gameover");
		LabelTTF* gameOverLabel = LabelTTF::create("Game Over","Marker Felt.ttf",visibleSize.width * 0.005);
		gameOverLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(gameOverLabel,100);
	}

	return true;
}

