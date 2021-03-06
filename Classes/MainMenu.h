//
// Created by RSANPUI on 7/7/2020.
//

#ifndef PROJ_ANDROID_MAINMENU_H
#define PROJ_ANDROID_MAINMENU_H

#include "cocos2d.h"
USING_NS_CC;

class MainMenu : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::CCObject* pSender);
    void GoToRulesScene( cocos2d::Ref *sender );
    CREATE_FUNC(MainMenu);
    void GoToLevelSetter( cocos2d::Ref *sender );
    void GoToGameScene( cocos2d::Ref *sender );
    void update(float dt);

    static float myScreenHeight, myScreenWidth, scaleFactor;
};

#endif //PROJ_ANDROID_MAINMENU_H
