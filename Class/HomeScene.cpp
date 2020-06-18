#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "HomeScene.h"
#include "HerosHomeScene.h"
#include "InfoScene.h"
#include "SettingScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
HomeScene::HomeScene() 
{
    //游戏界面设定
    this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    this->Origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
    
}
HomeScene::~HomeScene() {};

Scene* HomeScene::createScene()
{
    auto HomeLayer = Layer::create();
    auto scene= HomeScene::create();
    scene->addChild(HomeLayer, 0);
    return scene;
}


// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool HomeScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    //////////////////////////////////////////////////////
    //背景音乐设置
    if (BGMisPlay)
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("HomeSceneBGM.mp3", true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
    }

    ///////////////////////////////////////////////////////
    //背景层设置
    auto BackGround = Sprite::create("EntryScene2.png");
    if (BackGround == nullptr ||
        BackGround->getContentSize().width <= 0 ||
        BackGround->getContentSize().height <= 0)
    {
        problemLoading("EntryScene2.png");
    }
    else
    {
        BackGround->setPosition(0.5 * VisibleSize.width, 0.5 * VisibleSize.height);
        this->addChild(BackGround, 0);
    }

    //设置键
    auto setBTN = MenuItemImage::create(
        "SetNormal.png",
        "SetSelected.png",
        CC_CALLBACK_1(HomeScene::GoToSettingScene, this));

    if (setBTN == nullptr ||
        setBTN->getContentSize().width <= 0 ||
        setBTN->getContentSize().height <= 0)
    {
        problemLoading("'SetNormal.png' and 'SetSelected.png'");
    }

    //信息键
    auto infoBTN = MenuItemImage::create(
        "InfoNormal.png",
        "InfoSelected.png",
        CC_CALLBACK_1(HomeScene::GoToInfo, this));

    if (infoBTN == nullptr ||
        infoBTN->getContentSize().width <= 0 ||
        infoBTN->getContentSize().height <= 0)
    {
        problemLoading("'InfoNormal.png' and 'InfoSelected.png'");
    }

    //退出游戏
    auto closeItem = MenuItemImage::create(
        "returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HomeScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }

    auto menu1 = Menu::create(setBTN,infoBTN,closeItem,NULL);
    menu1->alignItemsVerticallyWithPadding(10);
    menu1->setPosition(Vec2(0.1*VisibleSize.width,0.2*VisibleSize.height));
    this->addChild(menu1, 1);

    //////////////////////////////////////////////////
    //开始游戏
    auto START = MenuItemLabel::create(Label::createWithTTF("START GAME", "fonts/Marker Felt.ttf", 24),
                            CC_CALLBACK_1(HomeScene::GoToHerosHome, this));

    if (START == nullptr ||
        START->getContentSize().width <= 0 ||
        START->getContentSize().height <= 0)
    {
        problemLoading("'START GAME'");
    }
    else
    {
        START->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.2));
    }

    auto menu2 = Menu::create(START, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);
    return true;
}


//退出游戏
void HomeScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->end();
}

//切换到HerosHome场景
void HomeScene::GoToHerosHome(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(HerosHome::createScene());
    //换音乐
    if (BGMisPlay)
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("HerosHome.mp3",true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
    }
}

//设置键
void HomeScene::GoToSettingScene(Ref* pSender)
{
    Director::sharedDirector()->pushScene(SettingScene::createScene());
}

//进入信息界面
void HomeScene::GoToInfo(Ref* pSender)
{
    Director::sharedDirector()->pushScene(InfoScene::createScene());
}
