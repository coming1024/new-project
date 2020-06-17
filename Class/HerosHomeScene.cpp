//场景创建
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "SettingScene.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "GameScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

HerosHome::HerosHome()
{
    //游戏界面设定
    this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    this->Origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0

    //背景音乐
    this->BGM = "HerosHome.mp3";

    //背景音乐音量
    this->BGMvolume = 0.5;

    //背景音乐是否播放
    this->BGMisPlay = true;

}
HerosHome::~HerosHome() {};

Scene* HerosHome::createScene()
{
    auto HerosHomeLayer = Layer::create();
    auto scene = HerosHome::create();
    scene->addChild(HerosHomeLayer, 0);
    return scene;
}

// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//初始化
bool HerosHome::init()
{
    if (!Scene::init())
    {
        return false;
    }



    /////////////////////////////////////////////////
    //背景图片设置

    auto BackGroundPicture = Sprite::create("HerosHome.png");
    if (BackGroundPicture == nullptr)
    {
        problemLoading("HerosHome.png");
    }
    else
    {
        BackGroundPicture->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
        this->addChild(BackGroundPicture,0);
    }

    auto SceneName = Label::createWithTTF("Heroes'home", "fonts/Marker Felt.ttf", 35);
    if (SceneName == nullptr ||
        SceneName->getContentSize().width <= 0 ||
        SceneName->getContentSize().height <= 0)
    {
        problemLoading("'SceneName'");
    }
    else
    {
        SceneName->setPosition(Vec2(VisibleSize.width * 0.5, VisibleSize.height * 0.94));
    }
    this->addChild(SceneName, 1);

    //返回键
    auto CloseItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HerosHome::BackToHomeScene, this));
    if (CloseItem == nullptr ||
        CloseItem->getContentSize().width <= 0 ||
        CloseItem->getContentSize().height <= 0)
    {
        problemLoading("'SceneName'");
    }
    else
    {
        CloseItem->setPosition(Vec2(0.95 * VisibleSize.width, 0.95 * VisibleSize.height));
    }
    

    //开始游戏
    auto StartBTN = MenuItemLabel::create(Label::createWithTTF("START", "fonts/Marker Felt.ttf", 30),
        CC_CALLBACK_1(HerosHome::GoToGameScene, this));
    if (StartBTN == nullptr ||
        StartBTN->getContentSize().width <= 0 ||
        StartBTN->getContentSize().height <= 0)
    {
        problemLoading("'PlayNormal.png'and 'PlaySelected.png'");
    }
    else
    {
        StartBTN->setColor(Color3B(189, 183, 107));
        StartBTN->setPosition(Vec2(0.5 * VisibleSize.width, 0.7 * VisibleSize.height));
    }
   
    
    ////////////
    auto menu1 = Menu::create(CloseItem, StartBTN,NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

    return true;
}

void HerosHome::BackToHomeScene(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(HomeScene::createScene());
}

void HerosHome::GoToGameScene(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(GameScene::createScene());
    if (BGMisPlay)
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameBGM.mp3", true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
    }
}
