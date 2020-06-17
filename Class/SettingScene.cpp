#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "GameScene.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "SettingScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

//������������
 float BGMvolume = 0.5;

//���������Ƿ񲥷�
 bool BGMisPlay = true;

SettingScene::SettingScene()
{
    //��Ϸ�����趨
    this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    this->Origin = Director::getInstance()->getVisibleOrigin();//origin��x,yֵ��Ϊ0
}
SettingScene::~SettingScene() {};

Scene* SettingScene::createScene()
{
    auto settingLayer = Layer::create();
    auto scene = SettingScene::create();
    scene->addChild(settingLayer);
    return scene;
}

// ����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//��ʼ��
bool SettingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //����
    auto SettingBackground = Sprite::create("EntryScene1.png");
    if (SettingBackground == nullptr||
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

    //���
    auto SettingBoard = Sprite::create("SetBackGround.png");
    if (SettingBoard == nullptr||
        SettingBoard->getContentSize().width <= 0 ||
        SettingBoard->getContentSize().height <= 0)
    {
        problemLoading("SetBackGround.png");
    }
    else
    {
        SettingBoard->setPosition(Vec2(0.5 * VisibleSize.width, 0.5 * VisibleSize.height));
        this->addChild(SettingBoard,0);
    }
    //��������
    auto BGMOnOff = MenuItemImage::create("MusicNormal.png",
        "MusicSelected.png",
        CC_CALLBACK_1(SettingScene::BGMControl, this));

    //��������
    auto volumeUp = MenuItemImage::create("addNormal.png",
                                        "addSelected.png",
        CC_CALLBACK_1(SettingScene::VolumeControl, this));
    //��������
    auto volumeDown = MenuItemImage::create("reduceNormal.png",
                                        "reduceSelected.png",
        CC_CALLBACK_1(SettingScene::VolumeControl, this));
    //���������Ӻ��������ټ���tag
    volumeUp->setTag(1);
    volumeDown->setTag(0);

    //�˵���
    auto menu1 = Menu::create(BGMOnOff,volumeDown, volumeUp, NULL);
    menu1->alignItemsHorizontallyWithPadding(10);
    menu1->setPosition(Vec2(0.5 * VisibleSize.width, 0.6 * VisibleSize.height));
    this->addChild(menu1, 1);
    /*
    auto MusicSlider = ControlSlider::create("MusicSlide1.png", "MusicSlide2.png", "sliderThumb.png");
    MusicSlider->setPosition(Vec2(VisibleSize.width*0.5,VisibleSize.height*0.6));
    MusicSlider->setMinimumValue(0);
    MusicSlider->setMaximumValue(1000);
    MusicSlider->setValue(500);
    MusicSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::BGMControl1), Control::EventType::VALUE_CHANGED);
    this->addChild(MusicSlider, 2);
    */

    //����������
    auto closeItem = MenuItemImage::create("returnNormal.png",
                                         "returnSelected.png",
        CC_CALLBACK_1(SettingScene::BackToLastScene, this));
    closeItem->setPosition(Vec2(0.9 * VisibleSize.width, 0.9 * VisibleSize.height));

    auto menu2 = Menu::create(closeItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    
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
        BGMisPlay=true;
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}
/*
void SettingScene::BGMControl1(Ref* pSender, Control::EventType event)
{
    ControlSlider* slider=(ControlSlider*)pSender;
    String* VolumeStr = String::createWithFormat("%f", slider->getValue());
    log(VolumeStr->getCString);
}
*/

//��������
void SettingScene::VolumeControl(cocos2d::Ref* pSender)
{

    int Item = ((CCMenuItemImage*)pSender)->getTag();
    if (Item == 0&& BGMvolume > 0.1)
    {
        BGMvolume -= 0.1;
    }
    if (Item == 1&& BGMvolume < 0.9)
    {
        BGMvolume += 0.1;
    }
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
}

//������һ������
void SettingScene::BackToLastScene(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->popScene();
}