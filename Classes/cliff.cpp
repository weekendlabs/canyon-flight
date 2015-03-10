#include "cliff.h"
#include "definitions.h"

USING_NS_CC;

Cliff::Cliff() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Cliff::spawnCliff1(cocos2d::Layer * layer) {
	float random = cocos2d::random(0.25, 0.45);

	Sprite* leftCliff = Sprite::create("cliff1.png");
	float leftCliffPosition = (visibleSize.width * random)
			+ leftCliff->getContentSize().width * -0.5;
	leftCliff->setPosition(
			Vec2(leftCliffPosition,
					visibleSize.height + leftCliff->getContentSize().height));
	layer->addChild(leftCliff, 1);

	Sprite* leftCliffShadow = Sprite::create("cliff1.png");
	leftCliffShadow->setColor(Color3B::BLACK);
	leftCliffShadow->setPosition(
			Vec2(leftCliffPosition + SCALE_640_WIDTH(5, visibleSize.width),
					visibleSize.height + leftCliff->getContentSize().height));
	layer->addChild(leftCliffShadow, 0);

	Sprite* rightCliff = Sprite::create("cliff1.png");
	rightCliff->setPosition(
			Vec2(
					leftCliffPosition + (0.45 * visibleSize.width)
							+ rightCliff->getContentSize().width,
					leftCliff->getPositionY()));
	layer->addChild(rightCliff, 1);

	Sprite* rightCliffShadow = Sprite::create("cliff1.png");
	rightCliffShadow->setColor(Color3B::BLACK);
	rightCliffShadow->setPosition(
			Vec2(
					leftCliffPosition + (0.45 * visibleSize.width)
							+ rightCliff->getContentSize().width + SCALE_640_WIDTH(-5, visibleSize.width) ,
					leftCliff->getPositionY()));
	layer->addChild(rightCliffShadow, 0);

	// ------ Moving the cliffs and shadows to the bottom ------
	MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

	leftCliff->runAction(moveBy);
	rightCliff->runAction(moveBy->clone());
	leftCliffShadow->runAction(moveBy->clone());
	rightCliffShadow->runAction(moveBy->clone());
}

void Cliff::spawnCliff2(cocos2d::Layer * layer) {
	Sprite* leftCliff = Sprite::create("cliff1.png");
	float random = cocos2d::random(0.45, 0.65);

	float leftCliffPosition = (visibleSize.width * random)
			+ leftCliff->getContentSize().width * -0.5;
	CCLOG("spawncliff2::random value:%f and its position:%f", random,
			leftCliffPosition);
	leftCliff->setPosition(
			Vec2(leftCliffPosition,
					visibleSize.height + leftCliff->getContentSize().height));
	layer->addChild(leftCliff, 1);

	Sprite* leftCliffShadow = Sprite::create("cliff1.png");
	leftCliffShadow->setColor(Color3B::BLACK);
	leftCliffShadow->setPosition(
			Vec2(leftCliffPosition + SCALE_640_WIDTH(5, visibleSize.width),
					visibleSize.height + leftCliff->getContentSize().height));
	layer->addChild(leftCliffShadow, 0);

	Sprite* rightCliff = Sprite::create("cliff1.png");
	rightCliff->setPosition(
			Vec2(
					leftCliffPosition + (0.45 * visibleSize.width)
							+ rightCliff->getContentSize().width,
					leftCliff->getPositionY()));
	layer->addChild(rightCliff, 1);

	Sprite* rightCliffShadow = Sprite::create("cliff1.png");
		rightCliffShadow->setColor(Color3B::BLACK);
		rightCliffShadow->setPosition(
				Vec2(
						leftCliffPosition + (0.45 * visibleSize.width)
								+ rightCliff->getContentSize().width + SCALE_640_WIDTH(-5, visibleSize.width) ,
						leftCliff->getPositionY()));
		layer->addChild(rightCliffShadow, 0);

	// ------ Moving the cliffs and shadows to the bottom ------
	MoveBy* moveBy = MoveBy::create(10, Vec2(0, -visibleSize.height * 1.2));

	leftCliff->runAction(moveBy);
	rightCliff->runAction(moveBy->clone());
	leftCliffShadow->runAction(moveBy->clone());
	rightCliffShadow->runAction(moveBy->clone());
}

