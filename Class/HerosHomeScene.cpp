//场景创建
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "SettingScene.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "GameScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

HerosHome::HerosHome()
{
    //游戏界面设定
    this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
    this->Origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0

}
HerosHome::~HerosHome() {};

Scene* HerosHome::createScene()
{
    auto HerosHomeLayer = Layer::create();
    auto scene = HerosHome::create();
    scene->addChild(HerosHomeLayer, 0);
    return scene;
}

// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//初始化
bool HerosHome::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //背景图片设置
    auto BackGroundPicture = Sprite::create("HerosHome.png");
    if (BackGroundPicture == nullptr)
    {
        problemLoading("HerosHome.png");
    }
    else
    {
        BackGroundPicture->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
        this->addChild(BackGroundPicture, 0);
    }

    auto SceneName = Label::createWithTTF("Heroes'home", "fonts/Marker Felt.ttf", 60);
    SceneName->setPosition(Vec2(VisibleSize.width * 0.5, VisibleSize.height * 0.95));
    this->addChild(SceneName, 1);
    //返回键
    auto CloseItem = MenuItemImage::create("returnNormal.png",
        "returnSelected.png",
        CC_CALLBACK_1(HerosHome::BackToHomeScene, this));
    CloseItem->setPosition(Vec2(0.95 * VisibleSize.width, 0.95 * VisibleSize.height));

    //信息键
    auto Infomation = MenuItemImage::create("infomation.png",
        "infomation1.png",
        CC_CALLBACK_1(HerosHome::InfoBTN, this));
    Infomation->setPosition(Vec2(0.25 * VisibleSize.width, 0.61 * VisibleSize.height));

    //开始游戏
    auto StartBTN = MenuItemLabel::create(Label::createWithTTF("START", "fonts/Marker Felt.ttf", 60),
        CC_CALLBACK_1(HerosHome::GoToGameScene, this));

    if (StartBTN == nullptr ||
        StartBTN->getContentSize().width <= 0 ||
        StartBTN->getContentSize().height <= 0)
    {
        problemLoading("'START GAME'");
    }
    else
    {
        StartBTN->setColor(Color3B(255, 255, 255));
        StartBTN->setPosition(Vec2(VisibleSize.width * 0.5, VisibleSize.height * 0.8));
    }

    auto menu1 = Menu::create(Infomation, CloseItem, StartBTN, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

    //信息界面


    InfoBoard = Sprite::create("HeroInfo1.png");
    InfoBoard->setVisible(false);
    InfoBoard->setPosition(Vec2(VisibleSize.width * 0.5, VisibleSize.height * 0.5));
    this->addChild(InfoBoard, 2);

    auto cache = SpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("oneHero.plist");
    //初始化英雄
    hero_qishi = qishi::create(cache, "one_r0.png");
    hero_qishi->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
    auto playerPos = hero_qishi->getPosition();
    this->addChild(hero_qishi, 1);
    //设置装备位置
    hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
    hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
    hero_qishi->_pt_bullets = CCArray::create();
    CC_SAFE_RETAIN(hero_qishi->_pt_bullets);
    //两种监听器
    auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(HerosHome::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(HerosHome::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(HerosHome::onTouchBegan, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(HerosHome::onTouchMoved, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(HerosHome::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

    this->schedule(schedule_selector(HerosHome::upDataHeroNature), 0.05f);
    this->schedule(schedule_selector(HerosHome::upDataAddEnergy), 1.5);

    return true;
}

void HerosHome::BackToHomeScene(cocos2d::Ref* pSender)
{
    if (InfoBoard->isVisible())
    {
        InfoBoard->setVisible(false);
        hero_qishi->resumeSchedulerAndActions();
    }
    else
    {
        Director::sharedDirector()->replaceScene(HomeScene::createScene());
    }

}

void HerosHome::GoToGameScene(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->replaceScene(LevelEnv::createScene());
    if (BGMisPlay)
    {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameBGM.mp3", true);
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMvolume);
    }
}

void HerosHome::InfoBTN(cocos2d::Ref* pSender)
{
    InfoBoard->setVisible(true);
    hero_qishi->pauseSchedulerAndActions();
}

void HerosHome::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
    if (hero_qishi->getDeath() == false)
    {
        if (keycode == EventKeyboard::KeyCode::KEY_J)
        {
            hero_qishi->swithWeapon(keycode, event);
        }
        if (keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_S
            || keycode == EventKeyboard::KeyCode::KEY_D || keycode == EventKeyboard::KeyCode::KEY_W
            || keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW
            || keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
        {
            hero_qishi->heroMove(keycode, event);
        }
    }
}

void HerosHome::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (hero_qishi->getDeath() == false)
    {
        if (hero_qishi->_isMoveing == true)
        {
            hero_qishi->heroStopMove(keycode, event);
        }
    }
}

bool HerosHome::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (hero_qishi->getDeath() == false)
    {
        hero_qishi->commonAttack(pTouch, pEvent);
        return true;
    }
    return false;
}
void HerosHome::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    /*if (hero_qishi->getDeath() == false)
    {
        if (hero_qishi->nowEquipment->_isContinue)
        {
            hero_qishi->commonAttack(pTouch, pEvent);
        }
    }*/
}
void HerosHome::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    if (hero_qishi->getDeath() == false)
    {
        hero_qishi->stopcommonAttack(pTouch, pEvent);
    }
}
void HerosHome::upDataHeroNature(float t)
{
    auto progress1 = (ProgressTimer*)hero_qishi->getBloodProgress();
    progress1->setPercentage((((float)hero_qishi->getCurrentLifeNum()) / (float)hero_qishi->getTotalLifeNum()) * 100);

    auto progress2 = (ProgressTimer*)hero_qishi->getEnergyProgress();
    progress2->setPercentage((((float)hero_qishi->getCurrentEnergy()) / (float)hero_qishi->getTotalEnergy()) * 100);

    auto progress3 = (ProgressTimer*)hero_qishi->getDefenceProgress();
    progress3->setPercentage((((float)hero_qishi->getCurrentDefence()) / (float)hero_qishi->getTotalDefence()) * 100);
}
void HerosHome::upDataAddEnergy(float t)
{
    hero_qishi->addCurrentEnergy(1);
}