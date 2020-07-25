//
// Created by RSANPUI on 7/7/2020.
//

#include "MainMenu.h"
#include "LevelSetter.h"

#define TRANSITION_TIME 0.5
#include "../cocos2d/cocos/deprecated/CCDeprecated.h"
//#include "../cocos2d/cocos/physics/CCPhysicsBody.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init() {
    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));

    // Closing menu
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Background Sprite
    auto backgroundSprite = Sprite::create("background/city11.png");
    //auto backgroundSprite = Sprite::create("city1.png");
    backgroundSprite->setPosition(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2);
    this->addChild(backgroundSprite, 0);

    // Game label
    auto label = Label::createWithTTF("Haunted City", "fonts/VerminVibesV-Zlg3.ttf", 30);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height -50));
    label->setTextColor(Color4B::WHITE);
    //label->enableOutline(Color4B::BLACK);
    this->addChild(label, 2);

    // Play menu
    auto playItem = MenuItemImage::create( "play-button.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::GoToLevelSetter, this ) );
    playItem->setPosition( Vec2( visibleSize.width / 2 + origin.x + 83, visibleSize.height / 6 + origin.y + 10) );
    playItem->setScale(1.5);
    auto menuPlay = Menu::create( playItem, NULL );
    menuPlay->setPosition( Point::ZERO );
    this->addChild( menuPlay, 2 );

    // Options menu
    auto playItem1 = MenuItemImage::create( "options-button.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::GoToLevelSetter, this ) );
    playItem1->setPosition( Vec2( visibleSize.width / 2 + origin.x + 60, visibleSize.height / 8 + origin.y ) );
    playItem1->setScale(1.5);
    auto menuPlay1 = Menu::create( playItem1, NULL );
    menuPlay1->setPosition( Point::ZERO );
    this->addChild( menuPlay1, 2 );

    // Quit
    auto playItem2 = MenuItemImage::create( "quit-button.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::menuCloseCallback, this ) );
    playItem2->setPosition( Vec2( visibleSize.width / 2 + origin.x + 15, visibleSize.height / 10 + origin.y ) );
    playItem2->setScale(1.5);
    auto menuPlay2 = Menu::create( playItem2, NULL );
    menuPlay2->setPosition( Point::ZERO );
    this->addChild( menuPlay2, 2 );

    return true;
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::GoToLevelSetter( cocos2d::Ref *sender )
{
    auto scene = LevelSetter::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
