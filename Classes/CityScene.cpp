//
// Created by rsanpui on 5/24/2020.
//

#include "CityScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "../cocos2d/cocos/math/Vec2.h"
#include "../cocos2d/cocos/base/CCRef.h"

USING_NS_CC;
int CityScene::SCORE = 0; // Initialize static variable

enum class PhysicsCategory {
    None = 0,
    Boulder = (1 << 0),    // 1
    Soldier = (1 << 1),   // 2
    Jewels = (1 << 2),    //4
    All = PhysicsCategory::Boulder | PhysicsCategory::Jewels // 5
};

Scene* CityScene::createScene()
{
    //return HelloWorld::create();
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    //CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    CityScene *layer = CityScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CityScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
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
            CC_CALLBACK_1(CityScene::menuCloseCallback, this));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    // Scoring section initialization
    SCORE = 0; // Re-initialize to zero.
    char text[256];
    sprintf(text,"SCORE: %d", SCORE);
    scoreLabel = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(Vec2(origin.x + scoreLabel->getContentSize().width,
                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 2);

    auto label = Label::createWithTTF("Haunted City", "fonts/Marker Felt.ttf", 24);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);


    // Parallax scrolling layers below with different speed
    city = ScrollingBg::create("city1.png", 4.0, 0.5, 0.7);
    this->addChild(city);


    schedule(schedule_selector(CityScene::update));
    initTouch();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("running.plist");
    auto frames = getAnimation("Run__00%d.png", 6);
    sprite3 = Sprite::createWithSpriteFrame(frames.front());
    sprite3->setPosition(Vec2(origin.x + visibleSize.width/3 -3, origin.y + visibleSize.height/3 + 6));


    initializePhysics(sprite3);
    sprite3->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Soldier);
    sprite3->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    sprite3->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::All);

    this->addChild(sprite3);

    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/8);
    sprite3->runAction(RepeatForever::create(Animate::create(animation)));

    schedule(schedule_selector(CityScene::addStones), 3);
    schedule(schedule_selector(CityScene::addJewels), 5);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(CityScene::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void CityScene::update(float dt)
{
    city->update(0.1);
}

void CityScene::initTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener -> onTouchBegan = [] (Touch* touch, Event* event) { return true;};
    listener -> onTouchMoved = CC_CALLBACK_2(CityScene::moveSprite, this);
    listener -> onTouchEnded = [=] (Touch* touch, Event* event) {};
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
}

void CityScene::moveSprite(Touch* touch, Event* evento)
{
    Vec2 touchLocation = touch->getLocation();
    Vec2 offset = touchLocation - sprite3->getPosition();

    if (offset.y > 0) {
        this->jumpSprite(sprite3);
    }
}

void CityScene::jumpSprite(CCSprite *mysprite){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCMoveBy *moveUp = CCMoveBy::create(0.2, Vec2(0, visibleSize.height*0.05));
    CCEaseInOut *easeMoveUp = CCEaseInOut::create(moveUp, 3.0);
    CCDelayTime *delay = CCDelayTime::create(0.5);
    CCAction *easeMoveDown = easeMoveUp->reverse();
    mysprite->runAction(CCSequence::create(easeMoveUp, delay, easeMoveDown, NULL));

}

Vector<SpriteFrame*> CityScene::getAnimation(const char *format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void CityScene::addJewels(float dt) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int random = (rand() % 30);
    Sprite* jewels;
/*
    if ((random % 4) == 0) {
        stones = Sprite::create("spikeA.png");
    }
    else {
        stones = Sprite::create("boulder.png");
    }
    */
    jewels = Sprite::create("gold-coin.png");

    // 1
    auto monsterContentSize = jewels->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height/2;
    int maxY = selfContentSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    jewels->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, visibleSize.height/4 -1 ));

    initializePhysics(jewels);
    jewels->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Jewels);
    jewels->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    jewels->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Soldier);
    jewels->getPhysicsBody()->setGravityEnable(false);

    this->addChild(jewels);

    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // 3
    //auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, visibleSize.height/2));
    auto actionMove = MoveTo::create(2, Vec2(-origin.x, visibleSize.height/3 -1));
    auto actionRemove = RemoveSelf::create();
    jewels->runAction(Sequence::create(actionMove,actionRemove, nullptr));

}

void CityScene::addStones(float dt) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int random = (rand() % 30);
    Sprite* stones;
/*
    if ((random % 4) == 0) {
        stones = Sprite::create("spikeA.png");
    }
    else {
        stones = Sprite::create("boulder.png");
    }
    */
    stones = Sprite::create("boulder.png");

    // 1
    auto monsterContentSize = stones->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height/2;
    int maxY = selfContentSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    stones->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, visibleSize.height/3 -1 ));

    initializePhysics(stones);
    stones->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Boulder);
    stones->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
    stones->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Soldier);

    this->addChild(stones);

    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // 3
    //auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, visibleSize.height/2));
    auto actionMove = MoveTo::create(2, Vec2(-origin.x, visibleSize.height/3 -1));
    auto actionRemove = RemoveSelf::create();
    stones->runAction(Sequence::create(actionMove,actionRemove, nullptr));

}

bool CityScene::onContactBegan(PhysicsContact &contact) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bodyA =  contact.getShapeA()->getBody();
    auto bodyB =  contact.getShapeB()->getBody();

    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (((bodyA->getCategoryBitmask() == (int) PhysicsCategory::Soldier )
        && (bodyB->getCategoryBitmask() == (int) PhysicsCategory::Boulder )) ||
        ((bodyB->getCategoryBitmask() == (int) PhysicsCategory::Soldier )
     && (bodyA->getCategoryBitmask() == (int) PhysicsCategory::Boulder )))
        {
        nodeA->removeFromParent();
        nodeB->removeFromParent();
        Director::getInstance()->end();
        return true;
    }

    if ((bodyA->getCategoryBitmask() == (int) PhysicsCategory::Soldier )
        && (bodyB->getCategoryBitmask() == (int) PhysicsCategory::Jewels ))
    {
        bodyB->getNode()->removeFromParent();
        //Director::getInstance()->end();
        SCORE++; // Score increment
        scoreLabel->setString("SCORE: " + std::to_string(SCORE));
        CCLOG("Increment score");
    }
    if ((bodyA->getCategoryBitmask() == (int) PhysicsCategory::Jewels )
     && (bodyB->getCategoryBitmask() == (int) PhysicsCategory::Soldier ))
    {
        bodyA->getNode()->removeFromParent();
        //Director::getInstance()->end();
        SCORE++; // Score increment
        scoreLabel->setString("SCORE: " + std::to_string(SCORE));
        CCLOG("Increment score");
     }

    //auto scene = GameOverScene::createScene();
    //Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );

    return true;
}

void CityScene::initializePhysics(Sprite* sprite)
{
    auto circle = PhysicsBody::createCircle(sprite -> getContentSize().width/2);
    //auto circle = PhysicsBody::createBox(Size(100.0f, 100.0f),
      //                                        PhysicsMaterial(0, 1, 0));
    circle->setContactTestBitmask(true);
    circle->setDynamic(true);
    sprite->setPhysicsBody(circle);
}

void CityScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
