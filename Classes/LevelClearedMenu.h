//
// Created by RSANPUI on 7/18/2020.
//


//
// Created by RSANPUI on 7/16/2020.
//

#ifndef PROJ_ANDROID_LEVELCLEAREDMENU_H
#define PROJ_ANDROID_LEVELCLEAREDMENU_H


#include "cocos2d.h"

class LevelClearedMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    int maxlevel; // This is the highest level the user has reached
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setGameLevel(cocos2d::CCObject* pSender);
    cocos2d::CCMenuItemImage* createMenuItem(int menulevel, int maxlevel);
    void GoToLevelSetter( cocos2d::Ref *sender );
    void GoToNextLevel( cocos2d::Ref *sender );
    void GoToGameScene( cocos2d::Ref *sender );
    const int kTagPlaygame = 1;
    const int kTagOptions = 2;

    // implement the "static create()" method manually
    CREATE_FUNC(LevelClearedMenu);
};

#endif //PROJ_ANDROID_LEVELCLEAREDMENU_H
