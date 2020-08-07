//
// Created by RSANPUI on 7/18/2020.
//

#include "LevelClearedMenu.h"

//
// Created by RSANPUI on 7/7/2020.
//

#include "LevelClearedMenu.h"
#include "SimpleAudioEngine.h"
#include "CityScene.h"
#include "GameOverScene.h"
#include "LevelSetter.h"
#include "MainMenu.h"
#include "PluginAdMob/PluginAdMob.h"

#define TRANSITION_TIME 0.5
static std::string kHomeBanner = "home";
static std::string kGameOverAd = "gameover";

USING_NS_CC;

Scene* LevelClearedMenu::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = LevelClearedMenu::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool LevelClearedMenu::init() {
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("running.ogg");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game-on.ogg",true);

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(LevelClearedMenu::menuCloseCallback, this));

    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));

    // Closing menu
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Background Sprite
    auto backgroundSprite = Sprite::create("scary2.jpg");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    backgroundSprite->setScale(2 * MainMenu::scaleFactor);
    this->addChild(backgroundSprite, 0);

    auto userdefaults = cocos2d::UserDefault::getInstance();
    if (GameOverScene::currentLevel < 12) { // Check-point to see we dont over-cross max level while incrementing
        GameOverScene::currentLevel +=1;
        //auto userdefaults = cocos2d::UserDefault::getInstance();
        if (GameOverScene::currentLevel > GameOverScene::highestLevel)
        {
            GameOverScene::highestLevel +=1;

            userdefaults->setIntegerForKey("highestLevel", GameOverScene::highestLevel);
        }
    }

    // Print next level and highest level
    char nextlevel[256];
    sprintf(nextlevel,"Next Level: %d",GameOverScene::currentLevel);
    auto gamenextlevel = Label::createWithTTF(nextlevel, "fonts/Marker Felt.ttf", 24);
    gamenextlevel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   origin.y + visibleSize.height/2 - 30));
    this->addChild(gamenextlevel, 2);


    auto highestScore = userdefaults->getIntegerForKey("highestScore");
    if (CityScene::SCORE > GameOverScene::highestScore)
    {
        GameOverScene::highestScore = CityScene::SCORE;
        //auto userdefaults = cocos2d::UserDefault::getInstance();
        userdefaults->setIntegerForKey("highestScore", highestScore);
    }


    // Settings menu
    auto playItem1 = MenuItemImage::create( "level-select/settings-level.png", "", CC_CALLBACK_1( LevelClearedMenu::GoToLevelSetter, this ) );
    playItem1->setPosition( Vec2( visibleSize.width / 2 + origin.x - 120, visibleSize.height / 2 + origin.y -150) );
    auto menuPlay1 = Menu::create( playItem1, NULL );
    menuPlay1->setScale(0.5 * MainMenu::scaleFactor);
    menuPlay1->setPosition( Point::ZERO );
    this->addChild( menuPlay1, 2 );

    // Re-try same level
    auto playItem2 = MenuItemImage::create( "level-select/retry-level.png", "", CC_CALLBACK_1( LevelClearedMenu::RetrySameLevel, this ) );
    playItem2->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y -150) );
    auto menuPlay2 = Menu::create( playItem2, NULL );
    menuPlay2->setScale(0.5 * MainMenu::scaleFactor);
    menuPlay2->setPosition( Point::ZERO );
    this->addChild( menuPlay2, 2 );

    // Next level
    auto playItem3 = MenuItemImage::create( "level-select/next-level.png", "", CC_CALLBACK_1( LevelClearedMenu::GoToNextLevel, this ) );
    playItem3->setPosition( Vec2( visibleSize.width / 2 + origin.x + 120, visibleSize.height / 2 + origin.y -150) );
    auto menuPlay3 = Menu::create( playItem3, NULL );
    menuPlay3->setScale(0.5 * MainMenu::scaleFactor);
    menuPlay3->setPosition( Point::ZERO );
    this->addChild( menuPlay3, 2 );


/*
    char text[256];
    sprintf(text,"Score: %d, Highest Score: %d",CityScene::SCORE, highestScore);
    auto scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 2);


*/
    sdkbox::PluginAdMob::show(kGameOverAd);
    return true;
}

void LevelClearedMenu::RetrySameLevel( cocos2d::Ref *sender )
{
    if (GameOverScene::currentLevel != 12) {
        GameOverScene::currentLevel -=1; // 12 is max-level, if someone re-tries same level, dont make them go to 11.
    }

    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    auto scene = CityScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void LevelClearedMenu::GoToLevelSetter( cocos2d::Ref *sender )
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    auto scene = LevelSetter::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void LevelClearedMenu::GoToNextLevel( cocos2d::Ref *sender )
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    auto scene = CityScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}


void LevelClearedMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

