#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "InfoScene.h"

#include "HomeScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

InfoScene::InfoScene()
{
    //游戏界面大小设定值
    this->VisibleSize = ParentScene::GetVisibleSize();
    this->Origin = ParentScene::GetOrigin();
}
InfoScene::~InfoScene() {};

Scene* InfoScene::createScene()
{
    auto infoLayer = Layer::create();
    auto scene = InfoScene::create();
    scene->addChild(infoLayer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool InfoScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //背景
    auto InfoBackGround = Sprite::create("EntryScene1.png");
    if (InfoBackGround == nullptr)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        InfoBackGround->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
        this->addChild(InfoBackGround,0);
    }

    //信息界面
    auto Infomation = Sprite::create("AttackInformation.png");
    if (InfoBackGround == nullptr)
    {
        problemLoading("AttackInformation.png");
    }
    else
    {
        Infomation->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
        this->addChild(Infomation,1);
    }

    //返回键
    auto closeItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(InfoScene::BackToLastScene, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'returnNormal.png' and 'returnSelected.png'");
    }
    else
    {
        closeItem->setPosition(Vec2(0.9*VisibleSize.width, 0.9*VisibleSize.height));
    }
    //菜单项
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

//返回键
void InfoScene::BackToLastScene(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->popScene();
}