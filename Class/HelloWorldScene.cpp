#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "HerosHomeScene.h"
#include "InfoScene.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


// ����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool HelloWorld::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    //��Ϸ�����С�趨ֵ
    auto visibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//origin��x,yֵ��Ϊ0

    //////////////////////////////////////////////////////
    //������������
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("EntrySceneBGM.mp3", true);


    //////////////////////////////////////////////////////
    //���ü�
    auto SETbtn = MenuItemImage::create(
        "SetNormal.png",
        "SetSelected.png",
        CC_CALLBACK_1(HelloWorld::Set, this));

    if (SETbtn == nullptr ||
        SETbtn->getContentSize().width <= 0 ||
        SETbtn->getContentSize().height <= 0)
    {
        problemLoading("'SetNormal.png' and 'SetSelected.png'");
    }
    else
    {
        
        SETbtn->setPosition(Vec2(0.1*visibleSize.width,0.23*visibleSize.height));
    }

    ///////////////////////////////////////////////
    //��Ϣ��
    auto Infobtn = MenuItemImage::create(
        "InfoNormal.png",
        "InfoSelected.png",
        CC_CALLBACK_1(HelloWorld::gotoInfo, this));

    if (Infobtn == nullptr ||
        Infobtn->getContentSize().width <= 0 ||
        Infobtn->getContentSize().height <= 0)
    {
        problemLoading("'InfoNormal.png' and 'InfoSelected.png'");
    }
    else
    {

        Infobtn->setPosition(Vec2(0.1 * visibleSize.width, 0.36 * visibleSize.height));
    }

    /////////////////////////////////////////////////////////////////////////
  //�˳���Ϸ
    auto closeItem = MenuItemImage::create(
        "returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        closeItem->setPosition(Vec2(0.1*visibleSize.width, 0.1*visibleSize.height));
    }

    //////////////////////////////////////////////////
    //��ʼ��Ϸ
    auto START = MenuItemLabel::create(Label::createWithTTF("START GAME", "fonts/Marker Felt.ttf", 24),
                            CC_CALLBACK_1(HelloWorld::startGame, this));

    if (START == nullptr ||
        START->getContentSize().width <= 0 ||
        START->getContentSize().height <= 0)
    {
        problemLoading("'START GAME'");
    }
    else
    {
        START->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.2));
        
    }

    
    //�˵���Ա
    SETbtn->setTag(1);
    Infobtn->setTag(2);

    auto interFace = Menu::create(SETbtn,Infobtn, closeItem, START,NULL);
    interFace->setPosition(Vec2::ZERO);
    this->addChild(interFace, 1);


    /////////////////////////////////////////////////////////
//������Ϸʱ�ı���
    auto entryBackGround = Sprite::create("EntryScene2.png");
    if (entryBackGround == nullptr)
    {
        problemLoading("EntryScene1.png");
    }
    else
    {
        entryBackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(entryBackGround, 0);
    }

    return true;

}

void HelloWorld::startGame(Ref* pSender)
{

    Director::sharedDirector()->replaceScene(HerosHome::createScene());
    //������
    if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("HerosHome.mp3", true);
    }

}

//�˳���Ϸ
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}



//���ü�
void HelloWorld::Set(Ref* pSender)
{
    CCDirector::sharedDirector()->pushScene(SettingScene::createScene());
}

void HelloWorld::gotoInfo(Ref* pSender)
{
    CCDirector::sharedDirector()->pushScene(InfoScene::createScene());
}




