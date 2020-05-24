#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
    


    //背景音乐的开关设置
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("EntrySceneBGM.mp3", true);
    auto BGMSet = MenuItemImage::create("BGMplaying.png", "BGMstopped.png",
        CC_CALLBACK_1(HelloWorld::stopMusic, this));

    if (BGMSet == nullptr ||
        BGMSet->getContentSize().width <= 0 ||
        BGMSet->getContentSize().height <= 0)
    {
        problemLoading("'BGMplaying.png'and 'BGMstopped.png'");
    }
    else
    {
        BGMSet->setPosition(Vec2(30+BGMSet->getContentSize().width / 2,
            30+BGMSet->getContentSize().height / 2));
    }


   //退出游戏
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    

 //加入菜单
    auto interFace = Menu::create(BGMSet,closeItem,NULL);
    interFace->setPosition(Vec2::ZERO);
    this->addChild(interFace, 1);

//进入游戏时的背景
    auto entryScene = Sprite::create("EntryScene1.png");
    if (entryScene == nullptr)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        entryScene->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(entryScene, 0);
    }
    

    return true;
}

//退出游戏
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//背景音乐的开关
void HelloWorld::stopMusic(Ref* pSender)
{
    if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    else
    {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    

}

