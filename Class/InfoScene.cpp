#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InfoScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene* InfoScene::createScene()
{
	return InfoScene::create();
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

    auto visibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0

    //背景
    auto InfoBackGround = Sprite::create("EntryScene1.png");
    if (InfoBackGround == nullptr)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        InfoBackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(InfoBackGround);
    }

    //信息
    auto Infomation = Sprite::create("AttackInformation.png");
    if (InfoBackGround == nullptr)
    {
        problemLoading("AttackInformation.png");
    }
    else
    {
        Infomation->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(Infomation);
    }
    //////////////////////////////////////
    auto closeItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(InfoScene::backtoHelloWorld, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'returnNormal.png' and 'returnSelected.png'");
    }
    else
    {
        closeItem->setPosition(Vec2(0.8*visibleSize.width, 0.8*visibleSize.height));
    }

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void InfoScene::backtoHelloWorld(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->popScene();
}