//场景创建
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

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
}
GameScene::~GameScene() {};

Scene* GameScene::createScene()
{
    auto GameLayer = Layer::create();
    auto scene = GameScene::create();
    scene->addChild(GameLayer, 0);
    return scene;
}

// 报错
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//初始化
bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto _PauseLayer = PauseLayer::create();
    this->addChild(_PauseLayer, 1);

        
}

void GameScene::BackToHomeScene()
{
    Director::sharedDirector()->replaceScene(HomeScene::createScene());
}