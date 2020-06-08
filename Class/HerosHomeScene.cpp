#include "cocos-ext.h"
#include "HerosHomeScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;


/////////////////////////////////////////////////////
//英雄选择界面
Scene* HerosHome::createScene()
{
    return HerosHome::create();
}

// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool HerosHome::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //游戏界面大小设定值
    auto visibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
    

    /////////////////////////////////////////////////
    //背景图片设置
    auto BackGroundPicture = Sprite::create("HerosHome.png");
    if (BackGroundPicture == nullptr)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        BackGroundPicture->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(BackGroundPicture);
    }


    //返回键
    auto CloseItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HerosHome::BackToHelloWorld, this));
    CloseItem->setPosition(Vec2(0.9 * visibleSize.width, 0.9 * visibleSize.height));

    auto menu = Menu::create(CloseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void HerosHome::BackToHelloWorld(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::createScene());
}