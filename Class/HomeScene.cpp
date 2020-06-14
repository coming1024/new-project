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
    //��Ϸ�����С�趨ֵ
    this->VisibleSize = ParentScene::GetVisibleSize();
    this->Origin = ParentScene::GetOrigin();
    this->BGM = "HomeSceneBGM.mp3";
}
HomeScene::~HomeScene() {};

Scene* HomeScene::createScene()
{
    auto HomeLayer = Layer::create();
    auto scene= HomeScene::create();
    scene->addChild(HomeLayer, 0);
    return scene;
}


// ����
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
    //������������
    if (ParentScene::GetBGMisPlay())
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(this->BGM, true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(this->BGMvolume);
    }

    ///////////////////////////////////////////////////////
    //����������
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

    //���ü�
    auto setBTN = MenuItemImage::create(
        "SetNormal.png",
        "SetSelected.png",
        CC_CALLBACK_1(HomeScene::GoToSettingLayer, this));

    if (setBTN == nullptr ||
        setBTN->getContentSize().width <= 0 ||
        setBTN->getContentSize().height <= 0)
    {
        problemLoading("'SetNormal.png' and 'SetSelected.png'");
    }

    //��Ϣ��
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

    //�˳���Ϸ
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
    //��ʼ��Ϸ
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


//�˳���Ϸ
void HomeScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->end();
}

//�л���HerosHome����
void HomeScene::GoToHerosHome(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(HerosHome::createScene());
    //������
    if (ParentScene::GetBGMisPlay())
    {

        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("HerosHome.mp3",true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(ParentScene::GetBGMvolume());
    }
}

//���ü�
void HomeScene::GoToSettingLayer(Ref* pSender)
{
    //ԭ���ĳ����仯
    /*
    BackGround->setTexture("EntryScene1.png");
    menu1->runAction(fadeout);
    START->runAction(fadeout);

    //�¾������
    SettingBackGround = Sprite::create("SetBackGround.png");//���ñ���
    if (SettingBackGround == nullptr ||
        SettingBackGround->getContentSize().width <= 0 ||
        SettingBackGround->getContentSize().height <= 0)
    {
        problemLoading("SetBackGround.png");
    }
    else
    {
        SettingBackGround->setPosition(Vec2(VisibleSize.width * 0.5, VisibleSize.height * 0.5));
    }
    SettingBackGround->setZOrder(2);

    //�������ƺͷ��ؼ�
    volumeUpBTN = MenuItemImage::create("addNormal.png",
        "addSelected.png",
        CC_CALLBACK_1(HomeScene::VolumeControl, this));
    volumeDownBTN = MenuItemImage::create("reduceNormal.png",
        "reduceSelected.png",
        CC_CALLBACK_1(HomeScene::VolumeControl, this));
    returnBTN = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HomeScene::VolumeControl, this));

    volumeUpBTN->setTag(1);
    volumeDownBTN->setTag(0);

    menu3 = Menu::create(volumeDownBTN, volumeUpBTN, NULL);
    menu3->alignItemsHorizontallyWithPadding(10);
    menu3->setPosition(Vec2(VisibleSize.width * 0.55, VisibleSize.height * 0.55));
    */
    Director::sharedDirector()->pushScene(SettingScene::createScene());
}

void HomeScene::GoToInfo(Ref* pSender)
{
    Director::sharedDirector()->pushScene(InfoScene::createScene());
}
