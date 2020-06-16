
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
    this->origin = Director::getInstance()->getVisibleOrigin();//origin��x,yֵ��Ϊ0
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
    //��ͣ�� test
    PauseItem = MenuItemImage::create("PauseNormal.png",
        "PauseSelected.png",
        CC_CALLBACK_1(PauseLayer::GotoPauseScene, this));
    PauseItem->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.9));

    auto  menu1 = Menu::create(PauseItem, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 0);

}

//ת����ͣ����
void PauseLayer::GotoPauseScene(cocos2d::Ref* pSender)
{

    //��ͣ����������
    Director::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

    PauseItem->setVisible(false);
    PauseItem->pause();
    //���뱳��
    BackGround = Sprite::create("SetBackGround.png");
    BackGround->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

    //������Ϸ
    auto ContinueBTN = MenuItemImage::create("PlayNormal.png",
        "PlaySelected.png",
        CC_CALLBACK_1(PauseLayer::BackToGame, this));
    //����������
    auto ReturnBTN = MenuItemImage::create("StopNormal.png",
        "StopSelected.png",
        CC_CALLBACK_1(PauseLayer::BackToHomeScene, this));
    //���ü�
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
//������Ϸ
void PauseLayer::BackToGame(cocos2d::Ref* pSender)
{
    PauseItem->setVisible(true);
    PauseItem->resume();

    //�Ƴ���ͣ��
    auto MoveAway1 = MoveBy::create(0.3f, Vec2(0, (menu->getContentSize().height * 0.5 + menu->getPosition().y)));
    menu->runAction(MoveAway1);

    //ȥ������
    auto MoveAway2 = MoveBy::create(0.3f, Vec2(0, (BackGround->getContentSize().height * 0.5 + BackGround->getPosition().y)));
    BackGround->runAction(MoveAway2);

    //�ָ���Ϸ������
    Director::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//ת�����ý���
void PauseLayer::GoToSettingScene(cocos2d::Ref* pSender)
{
    CCDirector::sharedDirector()->pushScene(SettingScene::createScene());
}


//����������
void PauseLayer::BackToHomeScene(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(HomeScene::createScene());
}