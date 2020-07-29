//
// Created by RSANPUI on 7/7/2020.
//

#include "GameOverScene.h"
#include "CityScene.h"
#include "SimpleAudioEngine.h"
#include "LevelSetter.h"

#define TRANSITION_TIME 0.5

int GameOverScene::highestScore = 0; // Initialize static variable
int GameOverScene::highestLevel = 1; // Initialize static variable
int GameOverScene::currentLevel = 1; // Initialize static variable

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = GameOverScene::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init() {
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("running.ogg");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game-on.ogg",true);


    // Background Sprite
    auto backgroundSprite = Sprite::create("background/city7.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    this->addChild(backgroundSprite, 0);


    auto gameover = Sprite::create("gameover/gameover1.png");
    gameover->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height/2 + 60);
    gameover->setScale(0.3);
    this->addChild(gameover, 1);

    // retry menu
    auto playItem1 = MenuItemImage::create( "gameover/retry.png", "CloseNormal.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    playItem1->setPosition( Vec2( visibleSize.width / 2 + origin.x - 120, visibleSize.height / 2 + origin.y -30) );
    auto menuPlay1 = Menu::create( playItem1, NULL );
    menuPlay1->setScale(0.7);
    menuPlay1->setPosition( Point::ZERO );
    this->addChild( menuPlay1, 2 );

    // Settings menu
    auto playItem2 = MenuItemImage::create( "gameover/settings.png", "CloseNormal.png", CC_CALLBACK_1( GameOverScene::GoToLevelSelect, this ) );
    playItem2->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y -30) );
    auto menuPlay2 = Menu::create( playItem2, NULL );
    menuPlay2->setScale(0.7);
    menuPlay2->setPosition( Point::ZERO );
    this->addChild( menuPlay2, 2 );

    // Exit menu
    auto playItem3 = MenuItemImage::create( "gameover/exit.png", "CloseNormal.png", CC_CALLBACK_1( GameOverScene::menuCloseCallback, this ) );
    playItem3->setPosition( Vec2( visibleSize.width / 2 + origin.x + 120, visibleSize.height / 2 + origin.y -30) );
    auto menuPlay3 = Menu::create( playItem3, NULL );
    menuPlay3->setScale(0.7);
    menuPlay3->setPosition( Point::ZERO );
    this->addChild( menuPlay3, 2 );



    auto userdefaults = cocos2d::UserDefault::getInstance();
    highestLevel = userdefaults->getIntegerForKey("highestLevel");
    highestScore = userdefaults->getIntegerForKey("highestScore");
    if (CityScene::SCORE > highestScore)
    {
        highestScore = CityScene::SCORE;
        userdefaults->setIntegerForKey("highestScore", highestScore);
    }

    // Score label
    char text[256];
    sprintf(text,"Score:");
    auto scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 20);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2 + 160 - 10,
                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 2);

    // Current score
    char text1[256];
    sprintf(text1,"Current: %d",CityScene::SCORE);
    auto scoreLabel1 = Label::createWithTTF(text1, "fonts/Marker Felt.ttf", 20);
    scoreLabel1->setPosition(Vec2(origin.x + visibleSize.width/2 + 160 + 20,
                                 origin.y + visibleSize.height - scoreLabel1->getContentSize().height - 20));
    this->addChild(scoreLabel1, 2);

    // Highest
    char text2[256];
    sprintf(text2,"Highest: %d",highestScore);
    auto scoreLabel2 = Label::createWithTTF(text2, "fonts/Marker Felt.ttf", 20);
    scoreLabel2->setPosition(Vec2(origin.x + visibleSize.width/2 + 160 + 25,
                                 origin.y + visibleSize.height - scoreLabel2->getContentSize().height - 40));
    this->addChild(scoreLabel2, 2);


    // Display max. level
    char maxlevel[256];
    sprintf(maxlevel,"Highest Level Cleared: %d",highestLevel);
    auto gamemaxlevel = Label::createWithTTF(maxlevel, "fonts/Marker Felt.ttf", 20);
    gamemaxlevel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/4 -10));
    this->addChild(gamemaxlevel, 2);

    return true;
}

void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    auto scene = CityScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameOverScene::GoToLevelSelect(CCObject* pSender)
{
    auto scene = LevelSetter::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
