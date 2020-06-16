#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "HomeScene.h"
#include "SettingScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

SettingScene::SettingScene()
{
    //��Ϸ�����С�趨ֵ
    this->VisibleSize = ParentScene::GetVisibleSize();
    this->Origin = ParentScene::GetOrigin();
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
    auto SettingBoard = Sprite::create("setBoard.png");
    if (SettingBoard == nullptr||
        SettingBoard->getContentSize().width <= 0 ||
        SettingBoard->getContentSize().height <= 0)
    {
        problemLoading("setBoard.png");
    }
    else
    {
        SettingBoard->setPosition(Vec2(0.5 * VisibleSize.width, 0.5 * VisibleSize.height));
        this->addChild(SettingBoard,0);
    }

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
    auto menu1 = Menu::create(volumeDown, volumeUp, NULL);
    menu1->alignItemsHorizontallyWithPadding(10);
    menu1->setPosition(Vec2(0.5 * VisibleSize.width, 0.7 * VisibleSize.height));
    this->addChild(menu1, 1);

    //����������
    auto closeItem = MenuItemImage::create("returnNormal.png",
                                         "returnSelected.png",
        CC_CALLBACK_1(SettingScene::BackToLastScene, this));
    closeItem->setPosition(Vec2(0.9 * VisibleSize.width, 0.9 * VisibleSize.height));

    auto menu2 = Menu::create(closeItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    
}

//��������
void SettingScene::VolumeControl(cocos2d::Ref* pSender)
{

    int Item = ((CCMenuItemImage*)pSender)->getTag();
    float Volume = ParentScene::GetBGMvolume();
    if (Item == 0&& Volume > 0.1)
    {
            Volume -= 0.1;
    }
    if (Item == 1&& Volume < 0.9)
    {
            Volume += 0.1;
    }
    ParentScene::SetBGMvolume(Volume);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(Volume);

}

void SettingScene::BackToLastScene(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->popScene();
}