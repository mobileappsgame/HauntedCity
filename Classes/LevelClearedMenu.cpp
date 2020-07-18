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

#define TRANSITION_TIME 0.5

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
    auto backgroundSprite = Sprite::create("level-select/level_cleared_screen.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    this->addChild(backgroundSprite, 0);

    GameOverScene::currentLevel +=1;
    auto userdefaults = cocos2d::UserDefault::getInstance();
    if (GameOverScene::currentLevel > GameOverScene::highestLevel)
    {
        GameOverScene::highestLevel +=1;

        userdefaults->setIntegerForKey("highestLevel", GameOverScene::highestLevel);
    }

    auto highestScore = userdefaults->getIntegerForKey("highestScore");
    if (CityScene::SCORE > GameOverScene::highestScore)
    {
        GameOverScene::highestScore = CityScene::SCORE;
        userdefaults->setIntegerForKey("highestScore", highestScore);
    }


    // Settings menu
    auto settingsItem = MenuItemImage::create( "level-select/settings-level.png", "CloseNormal.png", CC_CALLBACK_1( LevelClearedMenu::GoToLevelSetter, this ) );
    settingsItem->setPosition( Vec2( origin.x + 165, visibleSize.height/2 + origin.y -108 ) );

    auto settingsPlay = Menu::create( settingsItem, NULL );
    settingsPlay->setPosition( Point::ZERO );
    this->addChild( settingsPlay, 2 );

    // Re-try menu at same level
    auto retryLevelItem = MenuItemImage::create( "level-select/retry-level.png", "CloseNormal.png", CC_CALLBACK_1( LevelClearedMenu::GoToGameScene, this ) );
    retryLevelItem->setPosition( Vec2( origin.x + 165 + settingsItem->getContentSize().width + 20, visibleSize.height/2 + origin.y -108 ) );

    auto retryLevelPlay = Menu::create( retryLevelItem, NULL );
    retryLevelPlay->setPosition( Point::ZERO );
    this->addChild( retryLevelPlay, 2 );

    // Jump to next cleared level
    auto nextLevelItem = MenuItemImage::create( "level-select/next-level.png", "CloseNormal.png", CC_CALLBACK_1( LevelClearedMenu::GoToNextLevel, this ) );
    nextLevelItem->setPosition( Vec2( origin.x + 165 + settingsItem->getContentSize().width + 20 + retryLevelItem->getContentSize().width + 12, visibleSize.height/2 + origin.y -108 ) );
    nextLevelItem->setScale(0.7);
    auto nextLevelPlay = Menu::create( nextLevelItem, NULL );
    nextLevelPlay->setPosition( Point::ZERO );
    this->addChild( nextLevelPlay, 2 );


/*
    char text[256];
    sprintf(text,"Score: %d, Highest Score: %d",CityScene::SCORE, highestScore);
    auto scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 2);


*/
    return true;
}

void LevelClearedMenu::GoToGameScene( cocos2d::Ref *sender )
{
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

