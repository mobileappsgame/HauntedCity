//
// Created by rsanpui on 5/29/2020.
//

#ifndef PROJ_ANDROID_SCROLLINGBG_H
#define PROJ_ANDROID_SCROLLINGBG_H
#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class ScrollingBg: public CCNode {

public:
    static ScrollingBg* create(string name, float _speed, float _xpos, float _yPos);
    bool initScrollingBg(string _name, float _speed, float _xpos, float _yPos);

    CCSprite* gameBg1, *gameBg2;

    float speed;
    string name;

    CCSize winSize;

    void update(float dt);
};


#endif //PROJ_ANDROID_SCROLLINGBG_H
