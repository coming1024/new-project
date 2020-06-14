//场景创建
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Key.h"

#include "SettingScene.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "GameScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

HerosHome::HerosHome()
{
    //背景音乐
    this->BGM = "HerosHome.mp3";

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

    
    auto keyLayer = Key::create();
    this->addChild(keyLayer,1);

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

    //返回键
    auto CloseItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HerosHome::BackToHomeScene, this));
    CloseItem->setPosition(Vec2(0.9 * VisibleSize.width, 0.9 * VisibleSize.height));

    //开始游戏
    auto StartBTN = MenuItemImage::create("PlayNormal.png",
        "PlaySelected.png",
        CC_CALLBACK_1(HerosHome::GoToGameScene, this));
    StartBTN->setPosition(Vec2(0.5 * VisibleSize.width, 0.5 * VisibleSize.height));
    
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
    if (ParentScene::GetBGMisPlay())
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameBGM.mp3", true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(ParentScene::GetBGMvolume());
    }
}



