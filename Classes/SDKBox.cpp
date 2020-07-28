//
// Created by RSANPUI on 7/27/2020.
//

#include "SDKBox.h"
#include "PluginAdMob/PluginAdMob.h"


USING_NS_CC;

static std::string kHomeBanner = "home";
static std::string kGameOverAd = "gameover";
static std::string kRewardedAd = "rewarded";

int totalCoins = 0;

static std::function<void(const std::string &)> showText = nullptr;


class IMListener : public sdkbox::AdMobListener {
public:
    virtual void adViewDidReceiveAd(const std::string &name) {
        if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
        if (name == kHomeBanner) sdkbox::PluginAdMob::show(name);
    }
    virtual void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {
        if (showText) showText(StringUtils::format("%s\nname=%s,\nmsg=%s", __FUNCTION__, name.c_str(), msg.c_str()));

        float delay = 6; // seconds
        cocos2d::Director::getInstance()->getScheduler()->schedule([name](float) {
            cocos2d::log("cache %s again", name.c_str());
            sdkbox::PluginAdMob::cache(name);
        }, this, 0, 0, delay, false, "once");
    }
    virtual void adViewWillPresentScreen(const std::string &name) {
        if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewDidDismissScreen(const std::string &name) {
        if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewWillDismissScreen(const std::string &name) {
        if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewWillLeaveApplication(const std::string &name) {
        if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void reward(const std::string &name, const std::string &currency, double amount) {
        if (showText) {
            totalCoins += amount;
            showText(StringUtils::format("%s name=%s currency=%s amount=%lf total=%d",
                                         __FUNCTION__, name.c_str(), currency.c_str(), amount, totalCoins));
        }
    }
};


Scene* SDKBox::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SDKBox::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SDKBox::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CCLOG("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();

    // add quit button
   /* auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    */
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void SDKBox::createTestMenu()
{
    auto size = Director::getInstance()->getWinSize();

    auto label = Label::createWithSystemFont("Hello cpp", "Arial", 32);
    label->setPosition(size.width/2, 100);
    label->setColor(Color3B(255, 0, 0));
    addChild(label);

    showText = [=](const std::string &text) {
        CCLOG("%s", text.c_str());
        label->setString(text);
    };

    MenuItemFont::setFontName("Arial");

    // ui
    {
        Menu* menu = Menu::create(
                MenuItemFont::create("load banner", [](Ref*) { sdkbox::PluginAdMob::cache(kHomeBanner); }),
                MenuItemFont::create("show banner", [](Ref*) { sdkbox::PluginAdMob::show(kHomeBanner);  }),
                MenuItemFont::create("hide banner", [](Ref*) { sdkbox::PluginAdMob::hide(kHomeBanner);  }),
                MenuItemFont::create("is banner available", [=](Ref*) {
                    showText(StringUtils::format("is %s available %d", kHomeBanner.c_str(), sdkbox::PluginAdMob::isAvailable(kHomeBanner)));
                }),

                MenuItemFont::create("load interstitial", [](Ref*) { sdkbox::PluginAdMob::cache(kGameOverAd); }),
                MenuItemFont::create("show interstitial", [](Ref*) { sdkbox::PluginAdMob::show(kGameOverAd);  }),
                MenuItemFont::create("is interstital available", [=](Ref*) {
                    showText(StringUtils::format("is %s available %d", kGameOverAd.c_str(), sdkbox::PluginAdMob::isAvailable(kGameOverAd)));
                }),
                MenuItemFont::create("load rewarded video", [](Ref*) {
                    sdkbox::PluginAdMob::cache(kRewardedAd);
                }),
                MenuItemFont::create("show rewarded video", [](Ref*) {
                    sdkbox::PluginAdMob::show(kRewardedAd);
                }),
                NULL);
        menu->alignItemsVerticallyWithPadding(20);
        menu->setPosition(size.width/2, size.height/2);
        addChild(menu);
    }

    sdkbox::PluginAdMob::setListener(new IMListener());

}