//
// Created by RSANPUI on 7/7/2020.
//

#ifndef PROJ_ANDROID_CITYSCENE_H
#define PROJ_ANDROID_CITYSCENE_H

#include "cocos2d.h"
#include "ScrollingBg.h"
USING_NS_CC;
class CityScene : public cocos2d::CCLayer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    ScrollingBg *city;
    static int SCORE;
    cocos2d::Label* scoreLabel;

    // At each level you need to collect a certain number of coins to clear that level
    int coinsCollected;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    //void updatePosition();
    void update(float dt);
    //void scroll(float dt);
    void addStones(float dt);
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
    void initTouch();
    cocos2d::CCSprite *sprite3;
    void jumpSprite(cocos2d::CCSprite *mysprite);
    void shootArrows(float dt);
    void moveSprite(Touch* touch, Event* evento);
    void initializePhysics(cocos2d::Sprite* sprite);
    bool onContactBegan(cocos2d::PhysicsContact &contact);
    void addJewels(float dt);
    bool generateSpark();
    void initSounds();
    void addSkulls(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(CityScene);
};

#endif //PROJ_ANDROID_CITYSCENE_H
