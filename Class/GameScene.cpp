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

    //添加怪物(不带血条)
    monster1 = Monster::create();
    monster1->InitMonsterImage("monster.png");
    //monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");
    //monster1->setPosition(ccp(visibleSize.width - 150, visibleSize.height / 2));//？？？
    this->addChild(monster1, 1);
    //mymap->addChild(monster1);//将怪物添加到地图中，这样怪物才能随地图移动！！！！！///
    //monster1->StartListen(hero, mymap);

}

void GameScene::BackToHomeScene()
{
    Director::sharedDirector()->replaceScene(HomeScene::createScene());
}

///碰撞检测
bool GameScene::isRectCollision(CCRect rect1, CCRect rect2)
{
    float x1 = rect1.origin.x;//矩形1中心点的横坐标
    float y1 = rect1.origin.y;//矩形1中心点的纵坐标
    float w1 = rect1.size.width;//矩形1的宽度
    float h1 = rect1.size.height;//矩形1的高度
    float x2 = rect2.origin.x;
    float y2 = rect2.origin.y;
    float w2 = rect2.size.width;
    float h2 = rect2.size.height;

    if (x1 + w1 * 0.5 < x2 - w2 * 0.5)
        return false;//矩形1在矩形2左方，两者无碰撞
    else if (x1 - w1 * 0.5 > x2 + w2 * 0.5)
        return false;//矩形1在矩形2右方，两者无碰撞
    else if (y1 + h1 * 0.5 < y2 - h2 * 0.5)
        return false;//矩形1在矩形2下方，两者无碰撞
    else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)
        return false;//矩形1在矩形2上方，两者无碰撞

    return true;
}
