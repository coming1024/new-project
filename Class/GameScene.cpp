//��������
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Key.h"

#include "GameScene.h"
#include "SettingScene.h"
#include "HerosHomeScene.h"
#include "HomeScene.h"
#include "PauseLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

GameScene::GameScene()
{
    this->BGM = "HerosHome.mp3";
}
GameScene::~GameScene() {};

Scene* GameScene::createScene()
{
    auto GameLayer = Layer::create();
    auto scene = GameScene::create();
    scene->addChild(GameLayer, 0);
    return scene;
}

// ����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//��ʼ��
bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto _KeyLayer = Key::create();
    this->addChild(_KeyLayer, 0);

    auto _PauseLayer = PauseLayer::create();
    this->addChild(_PauseLayer, 1);

    //Ϊɶû��
    if (_KeyLayer->hero_qishi->_isDied)
    {
        auto GameOver = Label::createWithTTF("GameOver!", "fonts/Marker Felt.ttf", 24);
        BackToHomeScene();
    }
        
}

void GameScene::BackToHomeScene()
{
    Director::sharedDirector()->replaceScene(HomeScene::createScene());
}