
#include "PauseLayer.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "SettingScene.h"
#include "Key.h"

#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

PauseLayer::PauseLayer()
{
    this->visibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    this->origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
}
PauseLayer::~PauseLayer() {};

Layer* PauseLayer::createLayer()
{
    return PauseLayer::create();
}

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //////////////////////////////////////////////////////
    //暂停键 test
    PauseItem = MenuItemImage::create("PauseNormal.png",
        "PauseSelected.png",
        CC_CALLBACK_1(PauseLayer::GotoPauseScene, this));
    PauseItem->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.9));

    auto  menu1 = Menu::create(PauseItem, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 0);

}

//转到暂停界面
void PauseLayer::GotoPauseScene(cocos2d::Ref* pSender)
{

    //暂停动作和音乐
    Director::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

    PauseItem->setVisible(false);
    PauseItem->pause();
    //加入背景
    BackGround = Sprite::create("SetBackGround.png");
    BackGround->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

    //继续游戏
    auto ContinueBTN = MenuItemImage::create("PlayNormal.png",
        "PlaySelected.png",
        CC_CALLBACK_1(PauseLayer::BackToGame, this));
    //返回主界面
    auto ReturnBTN = MenuItemImage::create("StopNormal.png",
        "StopSelected.png",
        CC_CALLBACK_1(PauseLayer::BackToHomeScene, this));
    //设置键
    auto SettingBTN = MenuItemImage::create("SetNormal.png",
        "SetSelected.png",
        CC_CALLBACK_1(PauseLayer::GoToSettingScene, this));

    menu = Menu::create(ContinueBTN, ReturnBTN, SettingBTN, NULL);
    menu->alignItemsVerticallyWithPadding(10);
    menu->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(BackGround, 2);
    this->addChild(menu, 3);

}


//////////////////////////////////////////////////
//继续游戏
void PauseLayer::BackToGame(cocos2d::Ref* pSender)
{
    PauseItem->setVisible(true);
    PauseItem->resume();

    //移除暂停键
    auto MoveAway1 = MoveBy::create(0.3f, Vec2(0, (menu->getContentSize().height * 0.5 + menu->getPosition().y)));
    menu->runAction(MoveAway1);

    //去掉背景
    auto MoveAway2 = MoveBy::create(0.3f, Vec2(0, (BackGround->getContentSize().height * 0.5 + BackGround->getPosition().y)));
    BackGround->runAction(MoveAway2);

    //恢复游戏和音乐
    Director::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//转到设置界面
void PauseLayer::GoToSettingScene(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->pushScene(SettingScene::createScene());
}


//返回主界面
void PauseLayer::BackToHomeScene(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(HomeScene::createScene());
}