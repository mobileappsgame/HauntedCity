//
// Created by RSANPUI on 7/7/2020.
//

#include "MainMenu.h"
#include "LevelSetter.h"
#include "CityScene.h"
#include "SDKBox.h"
#include "PluginAdMob/PluginAdMob.h"

#define TRANSITION_TIME 0.5
#include "../cocos2d/cocos/deprecated/CCDeprecated.h"
//#include "../cocos2d/cocos/physics/CCPhysicsBody.h"
USING_NS_CC;
static std::string kHomeBanner = "home";
static std::string kGameOverAd = "gameover";
static std::string kRewardedAd = "rewarded";

class IMListener : public sdkbox::AdMobListener {
public:
    virtual void adViewDidReceiveAd(const std::string &name) {
        log("admob adViewDidReceiveAd %s: ", name.c_str());
        sdkbox::PluginAdMob::show(kHomeBanner);
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {
        CCLOG("*********** admob adViewDidFailToReceiveAdWithError %s: %s", msg.c_str(), name.c_str());

        float delay = 6; // seconds
        cocos2d::Director::getInstance()->getScheduler()->schedule([name](float) {
            cocos2d::log("cache %s again", name.c_str());
            sdkbox::PluginAdMob::cache(name);
        }, this, 0, 0, delay, false, "once");
        //if (showText) showText(StringUtils::format("%s name=%s, msg=%s", __FUNCTION__, name.c_str(), msg.c_str()));
    }
    virtual void adViewWillPresentScreen(const std::string &name) {
        CCLOG("admob adViewWillPresentScreen %s: ", name.c_str());
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewDidDismissScreen(const std::string &name) {
        CCLOG("admob adViewDidDismissScreen %s: ", name.c_str());
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewWillDismissScreen(const std::string &name) {
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));

        //if (name == "gameover") {
        //sdkbox::PluginAdMob::cache(kHomeBanner);
        //sdkbox::PluginAdMob::cache(kGameOverAd);
        //}
        CCLOG("admob adViewWillDismissScreen %s: ", name.c_str());
    }
    virtual void adViewWillLeaveApplication(const std::string &name) {
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
        CCLOG("admob adViewWillLeaveApplication %s: ", name.c_str());
    }
};

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

    //SDK Box call
    //sdkbox::PluginSdkboxAds::playAd("InterstitialAd","");

    /*sdkbox::PluginAdMob::cache("home");
    sdkbox::PluginAdMob::cache("gameover");

    sdkbox::PluginAdMob::show("home");
    sdkbox::PluginAdMob::show("gameover");
     */
    sdkbox::PluginAdMob::setListener(new IMListener());
    //schedule(schedule_selector(MainMenu::update));

    //return true;

    //auto scene = SDKBox::createScene();
    //Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );

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
    auto playItem = MenuItemImage::create( "play-button.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::GoToGameScene, this ) );
    playItem->setPosition( Vec2( visibleSize.width / 2 + origin.x + 15, visibleSize.height / 2 + origin.y ) );
    playItem->setScale(1.5);
    auto menuPlay = Menu::create( playItem, NULL );
    menuPlay->setPosition( Point::ZERO );
    this->addChild( menuPlay, 5 );

    // Options menu
    auto playItem1 = MenuItemImage::create( "options-button.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::GoToLevelSetter, this ) );
    playItem1->setPosition( Vec2( visibleSize.width / 2 + origin.x + 15, visibleSize.height / 2 + origin.y -50) );
    playItem1->setScale(1.5);
    auto menuPlay1 = Menu::create( playItem1, NULL );
    menuPlay1->setPosition( Point::ZERO );
    this->addChild( menuPlay1, 3 );

    // Quit
    auto playItem2 = MenuItemImage::create( "quit-button.png", "CloseNormal.png", CC_CALLBACK_1( MainMenu::menuCloseCallback, this ) );
    playItem2->setPosition( Vec2( visibleSize.width / 2 + origin.x + 15, visibleSize.height / 2 + origin.y -100) );
    playItem2->setScale(1.5);
    auto menuPlay2 = Menu::create( playItem2, NULL );
    menuPlay2->setPosition( Point::ZERO );
    this->addChild( menuPlay2, 4 );

    // Firebase AdMob
    // General scene setup ...




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

void MainMenu::GoToGameScene( cocos2d::Ref *sender )
{
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    auto scene = CityScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenu::update(float dt)
{
    //sdkbox::PluginAdMob::cache("home");
    //sdkbox::PluginAdMob::cache("gameover");

    sdkbox::PluginAdMob::show("home");
    //sdkbox::PluginAdMob::show("gameover");
}