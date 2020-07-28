//
// Created by RSANPUI on 7/27/2020.
//

#ifndef PROJ_ANDROID_SDKBOX_H
#define PROJ_ANDROID_SDKBOX_H

#include "cocos2d.h"

class SDKBox : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SDKBox);

    void createTestMenu();

};
#endif //PROJ_ANDROID_SDKBOX_H
