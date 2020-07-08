//
// Created by RSANPUI on 7/7/2020.
//

#include "ScrollingBg.h"

ScrollingBg* ScrollingBg::create(string _name, float _speed, float _xpos, float _yPos)
{

    ScrollingBg* ob = new ScrollingBg();
    if(ob && ob->initScrollingBg(_name, _speed, _xpos, _yPos))
    {
        ob->autorelease();
        return ob;
    }

    CC_SAFE_DELETE(ob);
    return NULL;

}

bool ScrollingBg::initScrollingBg(string _name, float _speed, float _xpos, float _yPos)
{
    winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    speed = _speed;

    gameBg1 = CCSprite::create(_name.c_str());

    gameBg1->setPosition(Vec2(origin.x + winSize.width * _xpos, origin.y + winSize.height * _yPos));
    //gameBg1->setScale(2.0f);
    //gameBg1->setScaleY(2.0f);
    gameBg1->setAnchorPoint(Vec2(0.5,0.5));

    addChild(gameBg1);

    gameBg2 = CCSprite::create(_name.c_str());
    gameBg2->setPosition(Vec2(origin.x + winSize.width * _xpos + winSize.width , origin.y + winSize.height * _yPos));
    //gameBg2->setScale(2.0f);
    //gameBg2->setScaleY(2.0f);
    gameBg2->setAnchorPoint(Vec2(0.5,0.5));

    addChild(gameBg2);

    return true;
}

void ScrollingBg::update(float dt)
{
    // scroll bg left or right
    CCPoint bg1pos = gameBg1->getPosition();
    gameBg1->setPosition(ccp((bg1pos.x - speed), bg1pos.y));


    if(gameBg1->getPosition().x < - winSize.width/2 )
        gameBg1->setPosition(ccp(winSize.width + winSize.width/2, gameBg1->getPosition().y));



    CCPoint bg2pos = gameBg2->getPosition();
    gameBg2->setPosition(ccp((bg2pos.x - speed), bg2pos.y));


    if(gameBg2->getPosition().x < - winSize.width/2 )
        gameBg2->setPosition(ccp(winSize.width + winSize.width/2,gameBg2->getPosition().y));

}
