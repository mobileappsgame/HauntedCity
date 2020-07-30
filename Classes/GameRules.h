//
// Created by RSANPUI on 7/30/2020.
//

#ifndef PROJ_ANDROID_GAMERULES_H
#define PROJ_ANDROID_GAMERULES_H
#include "cocos2d.h"

class GameRules : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameRules);
    void GoToMainMenu( cocos2d::Ref *sender );

};


#endif //PROJ_ANDROID_GAMERULES_H
