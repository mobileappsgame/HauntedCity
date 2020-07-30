//
// Created by RSANPUI on 7/30/2020.
//

#include "GameRules.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

#define TRANSITION_TIME 0.5

USING_NS_CC;

Scene* GameRules::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = GameRules::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameRules::init() {
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    // Background Sprite
    auto backgroundSprite = Sprite::create("horror.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    backgroundSprite->setScale(0.8);
    this->addChild(backgroundSprite, 0);


    // Exit menu
    auto playItem3 = MenuItemImage::create( "back.png", "CloseNormal.png", CC_CALLBACK_1( GameRules::GoToMainMenu, this ) );
    playItem3->setPosition( Vec2( visibleSize.width + origin.x + 570, visibleSize.height / 2 + origin.y -400) );
    auto menuPlay3 = Menu::create( playItem3, NULL );
    menuPlay3->setScale(0.2);
    menuPlay3->setPosition( Point::ZERO );
    this->addChild( menuPlay3, 2 );

    // Score label
    char text[2048];
    sprintf(text,"  Sam is returning home and loses his way and finds himself in the midst of a haunted city. \n\
    The game has in total 12 levels that you need to cross and at each level it becomes tougher.\n\n \
    Stones, spikes and shooting arrows are all targeted towards any traveler crossing the haunted city.\n\
    The blessing is Sam finds gold-coins on the way, help him collect as many as you can.\n\n\
    Boulders - Hop over them\n\
    Coins - Collect as many as you can\n\
    Skulls- Increases power on colliding");


    auto scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 10);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/2 - 10));
    //scoreLabel->setScale(0.9);
    this->addChild(scoreLabel, 2);

    return true;
}

void GameRules::GoToMainMenu( cocos2d::Ref *sender )
{
    auto scene = MainMenu::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}


