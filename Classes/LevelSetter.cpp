
//
// Created by RSANPUI on 7/16/2020.
//

#include "SimpleAudioEngine.h"
#include "CityScene.h"
#include "LevelSetter.h"
#include "GameOverScene.h"
#define TRANSITION_TIME 0.5

USING_NS_CC;

Scene* LevelSetter::createScene()
{
    return LevelSetter::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelSetterScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LevelSetter::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(LevelSetter::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


    // Background Sprite
    auto backgroundSprite = Sprite::create("level-select/level-select.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    this->addChild(backgroundSprite, 0);

    // In a real game, this should come from userdefaults:
    //auto userdefaults = cocos2d::UserDefault::getInstance();
    //maxlevel = userdefaults->getIntegerForKey("maxlevel");

    auto userdefaults = cocos2d::UserDefault::getInstance();
    //LevelSetter::maxlevel  This is the max level the player has cleared.
    LevelSetter::maxlevel = 1;
    if (LevelSetter::maxlevel < userdefaults->getIntegerForKey("highestLevel"))
    {
        LevelSetter::maxlevel = userdefaults->getIntegerForKey("highestLevel");
    }

    // Menu 1 button
    CCMenuItemImage* playItem1 = createMenuItem(1, LevelSetter::maxlevel);
    playItem1->setPosition( Vec2(origin.x + 80, visibleSize.height/2 + origin.y + 10 + 53) );
    playItem1->setTag(kTagPlaygame);
    auto menuPlay1 = Menu::create( playItem1, NULL );
    menuPlay1->setPosition( Point::ZERO );
    this->addChild(menuPlay1, 0);

    // Menu 2 button
    CCMenuItemImage* playItem2 = createMenuItem(2, LevelSetter::maxlevel);
    playItem2->setPosition( Vec2(origin.x + 80 + playItem1->getContentSize().width + 25, visibleSize.height/2 + origin.y + 10 + 53) );
    playItem2->setTag(kTagOptions);
    auto menuPlay2 = Menu::create( playItem2, NULL );
    menuPlay2->setPosition( Point::ZERO );
    this->addChild(menuPlay2, 0);

    // Menu 3 button
    CCMenuItemImage* playItem3 = createMenuItem(3, LevelSetter::maxlevel);
    playItem3->setPosition( Vec2(origin.x + 80 + playItem1->getContentSize().width + 25 + playItem2->getContentSize().width + 23, visibleSize.height/2 + origin.y + 10 + 53) );
    playItem3->setTag(kTagOptions);
    auto menuPlay3 = Menu::create( playItem3, NULL );
    menuPlay3->setPosition( Point::ZERO );
    this->addChild(menuPlay3, 0);

    // Menu 4 button
    CCMenuItemImage* playItem4 = createMenuItem(4, LevelSetter::maxlevel);
    playItem4->setPosition( Vec2(origin.x + 80 + playItem1->getContentSize().width + 25 + playItem2->getContentSize().width + 23 + playItem3->getContentSize().width + 25, visibleSize.height/2 + origin.y + 10 + 53) );
    playItem4->setTag(kTagOptions);
    auto menuPlay4 = Menu::create( playItem4, NULL );
    menuPlay4->setPosition( Point::ZERO );
    this->addChild(menuPlay4, 0);

    // Menu 5 button
    CCMenuItemImage* playItem5 = createMenuItem(5, LevelSetter::maxlevel);
    playItem5->setPosition( Vec2(origin.x + 80 + playItem1->getContentSize().width + 25 + playItem2->getContentSize().width + 23 + playItem2->getContentSize().width + 25 + playItem4->getContentSize().width + 25, visibleSize.height/2 + origin.y + 10 + 53) );
    playItem5->setTag(kTagOptions);
    auto menuPlay5 = Menu::create( playItem5, NULL );
    menuPlay5->setPosition( Point::ZERO );
    this->addChild(menuPlay5, 0);



    // Row 2
    // Menu 1 button
    CCMenuItemImage* playItem21 = createMenuItem(6, LevelSetter::maxlevel);
    playItem21->setPosition( Vec2(origin.x + 80, visibleSize.height/2 + origin.y -18) );
    playItem21->setTag(kTagPlaygame);
    auto menuPlay21 = Menu::create( playItem21, NULL );
    menuPlay21->setPosition( Point::ZERO );
    this->addChild(menuPlay21, 0);

    // Menu 2 button
    CCMenuItemImage* playItem22 = createMenuItem(7, LevelSetter::maxlevel);
    playItem22->setPosition( Vec2(origin.x + 80 + playItem21->getContentSize().width + 25, visibleSize.height/2 + origin.y -18) );
    playItem22->setTag(kTagOptions);
    auto menuPlay22 = Menu::create( playItem22, NULL );
    menuPlay22->setPosition( Point::ZERO );
    this->addChild(menuPlay22, 0);

    // Menu 3 button
    CCMenuItemImage* playItem23 = createMenuItem(8, LevelSetter::maxlevel);
    playItem23->setPosition( Vec2(origin.x + 80 + playItem21->getContentSize().width + 25 + playItem22->getContentSize().width + 25, visibleSize.height/2 + origin.y -18) );
    playItem23->setTag(kTagOptions);
    auto menuPlay23 = Menu::create( playItem23, NULL );
    menuPlay23->setPosition( Point::ZERO );
    this->addChild(menuPlay23, 0);

    // Menu 4 button
    CCMenuItemImage* playItem24 = createMenuItem(9, LevelSetter::maxlevel);
    playItem24->setPosition( Vec2(origin.x + 80 + playItem21->getContentSize().width + 25 + playItem22->getContentSize().width + 25 + playItem23->getContentSize().width + 25, visibleSize.height/2 + origin.y -18) );
    playItem24->setTag(kTagOptions);
    auto menuPlay24 = Menu::create( playItem24, NULL );
    menuPlay24->setPosition( Point::ZERO );
    this->addChild(menuPlay24, 0);

    // Menu 5 button
    CCMenuItemImage* playItem25 = createMenuItem(10, LevelSetter::maxlevel);
    playItem25->setPosition( Vec2(origin.x + 80 + playItem21->getContentSize().width + 25 + playItem22->getContentSize().width + 25 + playItem23->getContentSize().width + 25 + playItem24->getContentSize().width + 25, visibleSize.height/2 + origin.y -18) );
    playItem25->setTag(kTagOptions);
    auto menuPlay25 = Menu::create( playItem25, NULL );
    menuPlay25->setPosition( Point::ZERO );
    this->addChild(menuPlay25, 0);


    // Row 3
    // Menu 1 button
    CCMenuItemImage* playItem31 = createMenuItem(11, LevelSetter::maxlevel);
    playItem31->setPosition( Vec2(origin.x + 80, visibleSize.height/2 + origin.y -100) );
    playItem31->setTag(kTagPlaygame);
    auto menuPlay31 = Menu::create( playItem31, NULL );
    menuPlay31->setPosition( Point::ZERO );
    this->addChild(menuPlay31, 0);

    // Menu 2 button
    CCMenuItemImage* playItem32 = createMenuItem(12, LevelSetter::maxlevel);
    playItem32->setPosition( Vec2(origin.x + 80 + playItem21->getContentSize().width + 25, visibleSize.height/2 + origin.y -100) );
    playItem32->setTag(kTagOptions);
    auto menuPlay32 = Menu::create( playItem32, NULL );
    menuPlay32->setPosition( Point::ZERO );
    this->addChild(menuPlay32, 0);


    return true;
}

// This function sets the icon for menuitemimage based on maxlevel.
// if menulevel > maxlevel, then we place a "lock" sign, else it is enabled.
CCMenuItemImage* LevelSetter::createMenuItem(int menulevel, int maxlevel)
{

    char image[32];
    sprintf(image, "level-select/number%d.png",menulevel);

    CCMenuItemImage* playItem;

    if (menulevel <= LevelSetter::maxlevel)
    {
        playItem = MenuItemImage::create( image, image, CC_CALLBACK_1( LevelSetter::setGameLevel, this ) );
    }
    else {
        playItem = MenuItemImage::create( "level-select/lock.png", "lock.png", CC_CALLBACK_1( LevelSetter::setGameLevel, this ) );
    }

    return playItem;

}

void LevelSetter::setGameLevel(CCObject* pSender)
{
    CCMenuItemImage* pMenuItem = (CCMenuItemImage *)(pSender);
    int tag = (int)pMenuItem->getTag();
    CCLOG("***************** tag = %d *****************************",tag);

    if (tag > maxlevel)
        return; // The clicked level has not been cleared yet, so return

    switch (tag)
    {
        case 1:
            CCLOG("***************** Setting game level = 1 *****************************");
            GameOverScene::currentLevel = 1;
            GoToGameScene( this );
            break;
        case 2:
            CCLOG("****************** Setting game level = 2 *****************************");
            GameOverScene::currentLevel = 2;
            GoToGameScene( this );
            break;
        case 3:
            CCLOG("***************** Setting game level = 1 *****************************");
            GameOverScene::currentLevel = 3;
            GoToGameScene( this );
            break;
        case 4:
            CCLOG("****************** Setting game level = 2 *****************************");
            GameOverScene::currentLevel = 4;
            GoToGameScene( this );
            break;
        case 5:
            CCLOG("***************** Setting game level = 1 *****************************");
            GameOverScene::currentLevel = 5;
            GoToGameScene( this );
            break;
        case 6:
            CCLOG("****************** Setting game level = 2 *****************************");
            GameOverScene::currentLevel = 6;
            GoToGameScene( this );
            break;
        case 7:
            CCLOG("***************** Setting game level = 1 *****************************");
            GameOverScene::currentLevel = 7;
            GoToGameScene( this );
            break;
        case 8:
            CCLOG("****************** Setting game level = 2 *****************************");
            GameOverScene::currentLevel = 8;
            GoToGameScene( this );
            break;
        case 9:
            CCLOG("***************** Setting game level = 1 *****************************");
            GameOverScene::currentLevel = 9;
            GoToGameScene( this );
            break;
        case 10:
            CCLOG("****************** Setting game level = 2 *****************************");
            GameOverScene::currentLevel = 10;
            GoToGameScene( this );
            break;
        case 11:
            CCLOG("***************** Setting game level = 1 *****************************");
            GameOverScene::currentLevel = 11;
            GoToGameScene( this );
            break;
        case 12:
            CCLOG("****************** Setting game level = 2 *****************************");
            GameOverScene::currentLevel = 12;
            GoToGameScene( this );
            break;
        default:
            CCLOG("******************* Setting to default level = 0 ***************************");

    }
}


void LevelSetter::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void LevelSetter::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = CityScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}