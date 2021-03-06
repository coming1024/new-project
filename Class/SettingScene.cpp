#include "SimpleAudioEngine.h"

#include "GameScene.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "SettingScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

//背景音乐音量
float BGMvolume = 0.5;

//背景音乐是否播放
bool BGMisPlay = true;

SettingScene::SettingScene()
{
    //游戏界面设定
    this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    this->Origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
}
SettingScene::~SettingScene() {};

Scene* SettingScene::createScene()
{
    auto settingLayer = Layer::create();
    auto scene = SettingScene::create();
    scene->addChild(settingLayer);
    return scene;
}

// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//初始化
bool SettingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //背景
    auto SettingBackground = Sprite::create("EntryScene1.png");
    if (SettingBackground == nullptr ||
        SettingBackground->getContentSize().width <= 0 ||
        SettingBackground->getContentSize().height <= 0)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        SettingBackground->setPosition(Vec2(0.5 * VisibleSize.width, 0.5 * VisibleSize.height));
        this->addChild(SettingBackground);
    }

    //面板
    auto SettingBoard = Sprite::create("SetBackGround.png");
    if (SettingBoard == nullptr ||
        SettingBoard->getContentSize().width <= 0 ||
        SettingBoard->getContentSize().height <= 0)
    {
        problemLoading("SetBackGround.png");
    }
    else
    {
        SettingBoard->setPosition(Vec2(0.5 * VisibleSize.width, 0.5 * VisibleSize.height));
        this->addChild(SettingBoard, 0);
    }
    //音量开关
    auto BGMOnOff = MenuItemImage::create("MusicNormal.png",
        "MusicSelected.png",
        CC_CALLBACK_1(SettingScene::BGMControl, this));
    BGMOnOff->setPosition(Vec2(0.5 * VisibleSize.width, 0.55 * VisibleSize.height));

    auto MusicSlider = ControlSlider::create("MusicSlide1.png", "MusicSlide2.png", "sliderThumb.png");
    MusicSlider->setPosition(Vec2(VisibleSize.width * 0.5, VisibleSize.height * 0.5));
    MusicSlider->setMinimumValue(0);
    MusicSlider->setMaximumValue(1000);
    MusicSlider->setValue(BGMvolume * 1000);
    MusicSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::BGMControl1), Control::EventType::VALUE_CHANGED);
    this->addChild(MusicSlider, 1);


    //返回主界面
    auto closeItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(SettingScene::BackToLastScene, this));
    closeItem->setPosition(Vec2(0.9 * VisibleSize.width, 0.9 * VisibleSize.height));

    auto menu = Menu::create(closeItem, BGMOnOff, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


}

void SettingScene::BGMControl(cocos2d::Ref* pSender)
{
    if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        BGMisPlay = false;
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    else
    {
        BGMisPlay = true;
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}

void SettingScene::BGMControl1(cocos2d::Ref* pSender, Control::EventType event)
{
    ControlSlider* slider = (ControlSlider*)pSender;
    String* VolumeStr = String::createWithFormat("%f", slider->getValue());
    log(VolumeStr->getCString());
    BGMvolume = slider->getValue() / slider->getMaximumValue();
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
}


//音量控制
void SettingScene::VolumeControl(cocos2d::Ref* pSender)
{

    int Item = ((CCMenuItemImage*)pSender)->getTag();
    if (Item == 0 && BGMvolume > 0.1)
    {
        BGMvolume -= 0.1;
    }
    if (Item == 1 && BGMvolume < 0.9)
    {
        BGMvolume += 0.1;
    }
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
}

//返回上一个场景
void SettingScene::BackToLastScene(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->popScene();
}