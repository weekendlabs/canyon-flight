#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cliff.h"

class GameScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    Cliff cliff;

    cocos2d::Sprite* circle;

    cocos2d::Size visibleSize;

    float cliffSpawnRate;
    void spawnCliff();

    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);

    bool onContactBegin(cocos2d::PhysicsContact &contact);

    int score = 0;

    cocos2d::Label* scoreLabel;
    
    cocos2d::Vec2 circleVelocity = cocos2d::Vec2(0, 0);
    float deltaAccum;
    void update(float delta);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);


};

#endif // __GAME_SCENE_H__
