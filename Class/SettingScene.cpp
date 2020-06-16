#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;


Scene* SettingScene::createScene()
{
    return SettingScene::create();
}


// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SettingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
    //背景
    auto SettingBackground = Sprite::create("EntryScene1.png");
    if (SettingBackground == nullptr)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        SettingBackground->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));
        this->addChild(SettingBackground);
    }
    //面板
    auto SettingBoard = Sprite::create("setBoard.png");
    if (SettingBoard == nullptr)
    {
        problemLoading("setBoard.png");
    }
    else
    {
        SettingBoard->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));
        this->addChild(SettingBoard);
    }
    //音量增加
    auto volumeUp = MenuItemImage::create("addNormal.png",
                                        "addSelected.png",
        CC_CALLBACK_1(SettingScene::volumeControl, this));
    volumeUp->setPosition(Vec2(0.6 * visibleSize.width, 0.73 * visibleSize.height));
    //音量降低
    auto volumeDown = MenuItemImage::create("reduceNormal.png",
                                        "reduceSelected.png",
        CC_CALLBACK_1(SettingScene::volumeControl, this));
    volumeDown->setPosition(Vec2(0.5 * visibleSize.width, 0.73 * visibleSize.height));
    //返回主界面
    auto closeItem = MenuItemImage::create("returnNormal.png",
                                         "returnSelected.png",
        CC_CALLBACK_1(SettingScene::backtoHelloWorld, this));
    closeItem->setPosition(Vec2(0.8 * visibleSize.width, 0.8 * visibleSize.height));

    volumeUp->setTag(1);
    volumeDown->setTag(0);
    auto menu = Menu::create(volumeUp, volumeDown, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void SettingScene::volumeControl(cocos2d::Ref* pSender)
{
    int Item = ((CCMenuItemImage*)pSender)->getTag();
    float volume = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
    if (Item == 0&&volume>0.1)
    {
        volume += 0.1;
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    }
    if (Item == 1 && volume < 0.9)
    {
        volume -= 0.1;
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    }
}

void SettingScene::backtoHelloWorld(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->popScene();
}