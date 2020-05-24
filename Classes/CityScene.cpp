//
// Created by rsanpui on 5/24/2020.
//

#include "CityScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CityScene::createScene()
{
    //return HelloWorld::create();
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

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

    auto label = Label::createWithTTF("Haunted City", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }


    // background layer: another image
    background1 = Sprite::create("city1.png");
    // scale the image (optional)
    background1->setScale( 2.0f );
    // change the transform anchor point (optional)
    background1->setAnchorPoint( Vec2(0,0) );

    // Add second background
    // background layer: another image
    background2 = Sprite::create("city1.png");
    // scale the image (optional)
    background2->setScale( 2.0f );
    // change the transform anchor point (optional)
    background2->setAnchorPoint( Vec2(0,0) );
    this->addChild(background1);
    this->addChild(background2);
    // create a void node, a parent node
    //auto voidNode = ParallaxNode::create();


    //addChild( voidNode );
    schedule(schedule_selector(CityScene::scroll));
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(CityScene::addStones), 3);
    return true;
}

// update backgrounds
void CityScene::scroll(float dt) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CCPoint pos1 = background1->getPosition();
    CCPoint pos2 = background2->getPosition();

    pos1.x -= 3.0f;
    pos2.x -= 3.0f;

    if(pos1.x <=-(visibleSize.width) )
    {
        pos1.x = pos2.x + visibleSize.width;
    }

    if(pos2.x <=-(visibleSize.width) )
    {
        pos2.x = pos1.x + visibleSize.width;
    }
    background1->setPosition(pos1);
    background2->setPosition(pos2);
}

void CityScene::addStones(float dt) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto stones = Sprite::create("boulder_1.png");
    int random = (rand() % 30);
    Sprite* stones;
    if ((random % 4) == 0) {
        stones = Sprite::create("spikeA.png");
    }
    else {
        stones = Sprite::create("boulder_1.png");
    }

    // 1
    auto monsterContentSize = stones->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height/2;
    int maxY = selfContentSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    stones->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, visibleSize.height/2));
    this->addChild(stones);

    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // 3
    //auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, visibleSize.height/2));
    auto actionMove = MoveTo::create(3.0, Vec2(-monsterContentSize.width/2, visibleSize.height/2));
    auto actionRemove = RemoveSelf::create();
    stones->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

void CityScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
