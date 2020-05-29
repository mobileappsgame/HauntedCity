//
// Created by rsanpui on 5/24/2020.
//

#ifndef PROJ_ANDROID_CITYSCENE_H
#define PROJ_ANDROID_CITYSCENE_H

#include "cocos2d.h"
#include "ScrollingBg.h"

class CityScene : public cocos2d::CCLayer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //cocos2d::Sprite *background1;
    //cocos2d::Sprite *background2;
    ScrollingBg *city;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    //void updatePosition();
    void update(float dt);
    //void scroll(float dt);
    void addStones(float dt);
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);

    // implement the "static create()" method manually
    CREATE_FUNC(CityScene);
};
#endif //PROJ_ANDROID_CITYSCENE_H
